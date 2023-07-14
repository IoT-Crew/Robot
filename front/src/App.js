import React from "react";
import Home from "../src/home";
import Streaming from "./streaming";

function App() {
  return (
    <div className="app">
      <div className="home">
        <Home />
      </div>
      <div className="streaming">
        <Streaming />
      </div>
    </div>
  );
}

export default App;
