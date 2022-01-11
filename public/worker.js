import Module from './quantlib.js';

let CVAIRS = {
    "request":{
        "name":"calculateCVAIRS",
        "id":null,
        "todaysDate": "2004-03-10",
        "tenorsSwapMkt": {
            "1":5, 
            "2":10, 
            "3":15, 
            "4":20, 
            "5":25, 
            "6":30
        },
        "ratesSwapmkt":{
            "1": 0.03249, 
            "2": 0.04074, 
            "3": 0.04463, 
            "4": 0.04675, 
            "5": 0.04775, 
            "6": 0.04811
        },
        "defaultTenorsM":{
            "1":0, 
            "2":12, 
            "3":36, 
            "4":60, 
            "5":84, 
            "6":120, 
            "7":180, 
            "8":240, 
            "9":300, 
            "10":360
        },
        "intensities":{
            "low":[
                0.0036, 
                0.0036, 
                0.0065, 
                0.0099, 
                0.0111, 
                0.0177, 
                0.0177, 
                0.0177, 
                0.0177, 
                0.0177, 
                0.0177
            ],
            "medium":[
                0.0202, 
                0.0202, 
                0.0231, 
                0.0266, 
                0.0278, 
                0.0349, 
                0.0349, 
                0.0349, 
                0.0349, 
                0.0349,
                0.0349
            ],
            "high":[
                0.0534, 
                0.0534, 
                0.0564, 
                0.06, 
                0.0614, 
                0.0696,
                0.0696, 
                0.0696, 
                0.0696, 
                0.0696, 
                0.0696 
            ]          
        },
        "ctptyRR":{
                        "low":0.4,
                        "medium":0.35,
                        "high":0.3
        },
        "blackVol":0.15          
    },
    "response":{},
    "errors":{}
}
let data = JSON.stringify(CVAIRS)
 await Module()
 .then(pricer => console.log(pricer[`${JSON.parse(data).request.name}`](data)))
 .catch(e => console.log("ERROR IN WORKER: ", e)/*data.replace(new RegExp('errors:[', 'g'), `errors: [ ${e} ,`)*/)
 

self.onmessage = async ({ data } = evt) => 
self.postMessage
(
    await Module()
        .then(pricer => pricer[`${JSON.parse(data).request.name}`](data))
        .catch(e => console.log("ERROR IN WORKER: ", e)/*data.replace(new RegExp('errors:[', 'g'), `errors: [ ${e} ,`)*/)
)
  