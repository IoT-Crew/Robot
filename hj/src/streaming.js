import React from "react";
import "./home.css";

const Streaming = () => {
  return (
    <div className="video">
      <p>실시간 로봇 VIEW</p>
      <img className="picture" src="http://192.168.0.80:8080/video_feed"></img>
    </div>
  );
};

export default Streaming;
