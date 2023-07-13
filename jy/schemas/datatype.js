const mongoose = require('mongoose');
//데이터 모델링
const servoSchema = new mongoose.Schema({
  servo: { 
    type: Number, 
    required: true 
  },
  angle: { 
    type: Number, 
    required: true 
  }
});

const sensorSchema = new mongoose.Schema({
  data: { type: [servoSchema], required: true }
});

module.exports = mongoose.model('Sensor', sensorSchema);
