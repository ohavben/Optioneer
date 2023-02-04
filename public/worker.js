import optioneer from './optioneer.js';
/*
const data = {
    "request": {
        "excerciseStyle": 2,
        "id":"null",
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
}

optioneer().then(optioneer => console.log(optioneer.calculateOption(`${JSON.stringify(data)}`)))
*/

loadPricer(optioneer, 'calculateOption')

async function loadPricer(module, callback){
    await module()
        .then(m => self.onmessage = ({ data } = evt) => self.postMessage(m[`${callback}`](data)))
        .catch(e => console.log("error: could not load pricer: ", e))
}
