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
        <button className="Gauge">각도 Gauge 대시보드</button>{" "}
      </a>
      <div className="locationButton">
        <button className="A" onClick={() => handleAreaClick("A")}>
          A 구역
        </button>
        <button className="B" onClick={() => handleAreaClick("B")}>
          B 구역
        </button>
        <button className="C" onClick={() => handleAreaClick("C")}>
          C 구역
        </button>
        <button className="D" onClick={() => handleAreaClick("D")}>
          D 구역
        </button>
      </div>
      <div>
        <button className="CLOSE" onClick={() => handleAreaClick("E")}>
          CLOSE
        </button>
        <button className="OPEN" onClick={() => handleAreaClick("F")}>
          OPEN
        </button>
      </div>

      <img
        className="robotImage"
        src="https://cdn.pixabay.com/photo/2015/05/13/03/09/robots-764951_1280.png"
      />
    </div>
  );
}

export default Home;
