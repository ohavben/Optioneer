import React , { useState } from "react";
//import { option } from "../marketData"
import {_option_type } from "../utils"
//import { formik } 

type Props = {
    calculate:(data:_option_type) => Promise<string>
}

class Calculation extends React.Component<Props>{
    constructor(props:Props){
        super(props)
        this.handleClick = this.handleClick.bind(this)

        //console.log("calculation props: ", this.props)
        //console.log("calculation state: ", this.state)

    }

    async handleClick(){
        try {
            //let temp = option;
            //console.log(option)
            //temp.request.id = performance.now().toString();
            //let test = 
            console.log("click test: " ,  await this.props.calculate({
                "request": {
                    "excerciseStyle": 2,
                    "id":performance.now(),
                    "todaysDate":"1998-05-15",
                    "settlementDate": "1998-05-17",
                    "maturityDate": "1999-05-17",
                    "optionType":1,
                    "underlying": 36,
                    "strike": 40,
                    "dividendYield": 0,
                    "riskFreeRate": 0.06,
                    "optionPrice": 2.20
                },
                "response":{},
                "errors":{}
            }))
        }catch(error){
            console.log(`error in worker: ${error}`)
        }
        
        //try { return this.setState(JSON.parse(await this.props.calculate(this.state))) } 
        //catch (e) { return console.error(e) }
    }

    async componentDidMount() {
        //let test = await this.props.calculate(CVAIRS)
        //let test1 = await this.props.calculate(RegularBonds)
        //let test2 = await this.props.calculate(CVAIRS)
        //let test3 = await this.props.calculate(CVAIRS)
        //console.log("test  ", test)
        //console.log("test1  ", test1)
        //console.log("test2  ", test2)
        //console.log("test3  ", test3)
        try {
            //let calc = (await this.props.pricer(CVAIRS))
            this.setState({
                //marketData: JSON.stringify(JSON.parse(calc).request),
                //calcResult : JSON.stringify(JSON.parse(calc).response)  
            })
        } catch (e) {
            console.error(e);
        }
    }

    render(){

        return (
            <div>
                <h1>Calculation</h1>
                <br/>
                <hr/>
                <div>
                    <form>
                        <input type = 'text' name='info' aria-label='info'></input>
                    </form>
                </div>
                <div>
                    Response: 
                    <br/>
                    <br/>
                    <span>
                        Response: {JSON.stringify(this.state)}
                    </span>
                    <br/>
                    <hr/>
                </div>
                <button onClick={this.handleClick}>
                    Calculate
                </button>
            </div>
        )
    }
    /*
    render(){
        return (
            <div>
                <h2>Calculation</h2>
                <br/>
                <hr/>
                <div>
                    <br/>
                    <span>Request: {this.state.marketData}</span>
                    <br/>
                    <hr/>
                </div>
                <div>
                    Response: 
                    <br/>
                    <br/>
                    <span>
                        Response: {this.state.calcResult}
                    </span>
                    <br/>
                    <hr/>
                </div>
                <button onClick={this.handleClick}>
                    Calculate
                </button>
            </div>
        )
    }*/
}
   

export default Calculation