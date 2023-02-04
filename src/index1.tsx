import React from "react";
import ReactDOM from "react-dom";
import App from "./components/App"
import { pricer } from "./utils";

ReactDOM.render( 
  <React.StrictMode>
    <App App = {
      { 
        "dbName": "mydb" ,
        "pricer":pricer('worker.js'),
        "dimensions":{
          "width": window.innerWidth,
          "height": window.innerHeight, 
        }
      }
    }/>
  </React.StrictMode>,
  document.getElementById("root")
)


/*import React from 'react';
import ReactDOM from 'react-dom';
import './index.css';
import App from './App';
import reportWebVitals from './reportWebVitals';

ReactDOM.render(
  <React.StrictMode>
    <App />
  </React.StrictMode>,
  document.getElementById('root')
);

// If you want to start measuring performance in your app, pass a function
// to log results (for example: reportWebVitals(console.log))
// or send to an analytics endpoint. Learn more: https://bit.ly/CRA-vitals
reportWebVitals();*/
