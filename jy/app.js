//index의 파일을 import해서 화면 app으로 실행되는 곳
const express = require('express');
const bodyParser = require('body-parser');

//몽고DB 연결
const connect = require('../jy/schemas/connectDB');
const port = 3000;



//몽고DB연결
connect();

//서버 연결
const app = express();
// app.use(cors);



// app.listen(port,()=>{
//     console.log(`실행중 http://localhost:${port}`);
// });