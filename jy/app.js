//index의 파일을 import해서 화면 app으로 실행되는 곳
const express = require('express');
const bodyParser = require('body-parser');

/*DataBase*/
const Sensor = require('../jy/schemas/datatype');

//몽고DB 연결
const connect = require('../jy/schemas/connectDB');
 
const port = process.env.PORT || 3000;
const path = require('path'); 


//몽고DB연결
connect();

//서버 연결
const app = express();
app.use(bodyParser.json());

app.set('view engine', 'ejs'); 
app.set('views', path.join(__dirname, 'views')); 
app.use(express.urlencoded({extended : false}));

app.get('/', (req, res)=>{//   '/'의 주소를 받은 경우
    res.render('home')  // views의 home을 랜더링하여 보여줌
});
 
app.get('/sensor', async(req, res)=>{
    const sensors = await Sensor.find({}); // DB의 모든 내용을 cafes에 저장
    res.render('sensor', {sensors}); // 해당 객체를 cafe.ejs로 넘겨줌
})
 
app.post('/sensor', async(req, res)=>{//create cafe
    // const sensor = new Sensor(req.body);
    console.log(req.body);
    const {data} = req.body;
    const sensor = new Sensor({ data })
    await sensor.save(); // document 생성 및 저장
    // res.redirect('/'); // /cafe주소로 리다이렉트
})


app.listen(port,()=>{
    console.log(`실행중 http://localhost:${port}`);
});