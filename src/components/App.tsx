import React, {Component} from "react";
//import { debounce, throttle, randomString, broweserPrefix } from "./utils";
//import { cssRules, /*icons*/ } from "./css/css_rules";
//import Footer from "./components/Footer";
//import Header from "./components/Header";
//import LeftSideBar from "./components/LeftSideBar";
//import RightSideBar from "./components/RightSideBar";
//import MainContent from "./components/MainContent";
import Calculation from "./Calculation";
import {_option_type } from "../utils"

type Props = {
    App : {
        "dbName": string,
        "pricer":{ analyze: (data: _option_type) => Promise<string> },
        "dimensions":{
          "width":number,
          "height":number
        }
    }
}

type State = {}

class App  extends Component <Props, State>{
  /*constructor(props:Props){
    super(props)
  }*/

  render (){
    return (
      <React.StrictMode>
        <Calculation calculate = { this.props.App.pricer.analyze } />
      </React.StrictMode>
    )
  }
}

export default App;


/*import React from 'react';
import logo from './logo.svg';
import './App.css';

function App() {
  return (
    <div className="App">
      <header className="App-header">
        <img src={logo} className="App-logo" alt="logo" />
        <p>
          Edit <code>src/App.tsx</code> and save to reload.
        </p>
        <a
          className="App-link"
          href="https://reactjs.org"
          target="_blank"
          rel="noopener noreferrer"
        >
          Learn React
        </a>
      </header>
    </div>
  );
}

export default App;*/
