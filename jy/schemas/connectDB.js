const mongoose = require('mongoose');
//몽고 연결
const connect = () => {
  if (process.env.NODE_ENV !== 'production') {
    mongoose.set('debug', true);
  }
  mongoose.connect('mongodb+srv://traum077045:0000@user.ld9fipj.mongodb.net/', {
    dbName: 'test',
    useNewUrlParser: true,
  }).then(() => {
    console.log("몽고디비 연결");
  }).catch((err) => {
    console.error("몽고디비 연결 에러", err);
  });
};

mongoose.connection.on('error', (error) => {
  console.error('몽고디비 연결 에러', error);
});
mongoose.connection.on('disconnected', () => {
  console.error('몽고디비 연결이 끊겼습니다. 연결을 재시도합니다.');
  connect();
});

module.exports = connect;
