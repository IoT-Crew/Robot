import React from "react";
import "./home.css";

function Home() {
  return (
    <div className="Home">
      <a
        href="http://192.168.0.101:1880/ui/#!/1?socketid=OdY7fmNICnTr9ThUAAAD"
        target="_blank"
        rel="noopener noreferrer"
      >
        <button className="Gauge">실시간 각도 Gauge 대시보드</button>{" "}
      </a>
      <div>
        <button className="A">A 구역</button>
        <button className="B">B 구역</button>
      </div>
      <div>
        <button className="C">C 구역</button>
        <button className="D">D 구역</button>
      </div>
    </div>
  );
}
export default Home;
