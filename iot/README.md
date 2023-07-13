# 07.11
아두이노 제어 SW 개선 진행 중

- 기존 라이브러리가 그립퍼부터 동작을 지멋대로 하고 있어서 골치가 아파 내가 한다.


# 07.13
Node-red function 설명

```js
var sensorData = msg.payload;

if (typeof sensorData === 'string') {
    // try 블록 안에 코드에 에러 발생 -> catch error handling
    try {
        sensorData = JSON.parse(sensorData);
        msg.payload = sensorData;
        return msg
    } catch (error) {
        // JSON.parse()에서 오류 발생 시, 유효하지 않은 데이터로 처리
        sensorData = null;
        msg.payload = sensorData;
        return msg
    }
}

// return sensorData;
```

```js
// @ts-nocheck
// @ts-ignore
var sensorData = msg.payload;

if (sensorData && sensorData.data && Array.isArray(sensorData.data)) {

    // 대시보드에서 Gauge에 표시할 값을 생성
    var gaugeData = {label: "Servo " + sensorData.data[0].servo, value: sensorData.data[0].angle };


    // Guage에 표시할 값을 msg.gaugeData에 할당
    msg.payload = gaugeData;
    // return gaugeData;
    return msg
} else {
    return null; // 유효한 데이터가 아닌 경우 메시지를 건너뛴다.
    // return msg
}
```