import React from "react";
import axios from "axios";
import "./home.css";

function Home() {
  const handleAreaClick = (area) => {
    axios
      .get(`http://192.168.0.80:1880/area?data=${area}`) // Node-RED 플로우 실행 엔드포인트와 필요한 데이터 전송
      .then((response) => {
        // 요청에 대한 응답 처리
        console.log(response.data); //응답 데이터 출력
      })
      .catch((error) => {
        // 오류 처리
        console.error(error); //오류 출력
      });
  };

  return (
    <div className="Home">
      <a
        href="http://192.168.0.80:1880/ui"
        target="_blank"
        rel="noopener noreferrer"
      >
        <button className="Gauge">실시간 각도 Gauge 대시보드</button>{" "}
      </a>
      <div className="locationButton">
        <div>
          <button className="A" onClick={() => handleAreaClick("A")}>
            A 구역
          </button>
          <button className="B" onClick={() => handleAreaClick("B")}>
            B 구역
          </button>
        </div>
        <div>
          <button className="C" onClick={() => handleAreaClick("C")}>
            C 구역
          </button>
          <button className="D" onClick={() => handleAreaClick("D")}>
            D 구역
          </button>
        </div>
        <div>
          <button className="Catch" onClick={() => handleAreaClick("E")}>
            CLOSE
          </button>
          <button className="Put" onClick={() => handleAreaClick("F")}>
            OPEN
          </button>
        </div>
      </div>
    </div>
  );
}

export default Home;
