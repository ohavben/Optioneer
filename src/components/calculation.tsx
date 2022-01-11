import React , { useState } from "react";
import {
     _RegularBonds_Type,
     _CVAIRS_Type,
    _ConvertibleBonds_Type, 
    _CallableBonds_Type,
    _RegularBonds_Interface,
     _CVAIRS_Interface,
    _ConvertibleBonds_Interface, 
    _CallableBonds_Interface
} from "../marketDataInterface"
import { RegularBonds, CVAIRS, ConvertibleBonds, CallableBonds } from "../marketData"
//import { formik } 
type Props = {
    calculate:(data:_RegularBonds_Type | _CVAIRS_Type | _ConvertibleBonds_Type | _CallableBonds_Type) => Promise<string>
}

class Calculation extends React.Component<Props>{
    constructor(props:Props){
        super(props)
        /*this.state = JSON.parse(JSON.stringify(this.props.marketData))/*{ 
            rawData: JSON.parse(JSON.stringify(this.props.marketData.request)),
            marketData: JSON.stringify(this.props.marketData.request),
            calcResult: null
        };*/
        this.handleClick = this.handleClick.bind(this)

        console.log("calculation props: ", this.props)
        console.log("calculation state: ", this.state)

    }

    async handleClick(){
        try {
            let temp = CVAIRS;
            temp.request.id = performance.now().toString();
            console.log("CVAIRS: ", CVAIRS.request.id)
            console.log("temp: ", temp.request.id)
            let test = await this.props.calculate(temp)
            console.log("click test: " , test)
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