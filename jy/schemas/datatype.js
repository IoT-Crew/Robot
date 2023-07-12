const mongoose = require('mongoose');
//데이터 모델링
const { Schema } = mongoose;
const sensorSchema = new Schema({
  type: {
    type: String,
    required: true,
  },
  value: {
    type: Number,
    required: true,
  },
  createdAt: {
    type: Date,
    default: Date.now,
  },
});

module.exports = mongoose.model('Sensor', sensorSchema);
