import React from 'react';
import logo from './logo.svg';
import { Pricer } from './features/pricer/Pricer';
import './css/App.css';

function App() {
  return (
    <div className="App">
      <header className="App-header">
        <Pricer />
      </header>
    </div>
  );
}

export default App;
