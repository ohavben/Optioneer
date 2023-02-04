export interface optionValuation {
    "request": {
      "excerciseStyle": 0 | 1 | 2,
      "id":number,
      "todaysDate":string,
      "settlementDate": string,
      "maturityDate": string,
      "optionType": 1 | -1,
      "underlying": number,
      "strike": number,
      "dividendYield": number,
      "riskFreeRate": number,
      "optionPrice": number
    },
    "response":{},
    "errors":{}
  }

interface Subscription {
    id:number;
    resolve: (value: optionValuation | PromiseLike<optionValuation>) => void;
    reject:  (reason?: any) => void;
}

export default function pricer (url:string){

    console.log('Slice worker')

    let subs = new Map(), pricer = new Worker(`${url}`, { type: 'module' });

    pricer.onmessage = workerListerner;

    pricer.onerror = (e => console.log("ERROR in worker: ", e))

    function workerListerner(event: { data: string }){
        
        let { data } =  event;
        let calaculationResponse:optionValuation = JSON.parse(data);
        let key = calaculationResponse.request.id;
        console.log('response id: ', key)
        let response = subs.get(key)

        if (!response) {
            console.log(`no subsciption found for key ${key}`)
            return
        }
        response.resolve(calaculationResponse)
        subs.delete(key)
        return 
    }

    function publish(sub:Subscription, data:optionValuation){
        if (data.request.id){
            subs.set(data.request.id, sub)
            return pricer.postMessage(JSON.stringify(data))
        } else {
            return sub.reject('no id sent')
        } 
    }

    function subscribe (data: optionValuation):Promise<optionValuation> {
        console.log('request id: ', data.request.id)
        return new Promise((resolve, reject) => {
            return (data.request.id)
            ?publish({
                id: data.request.id,
                resolve: resolve,
                reject: reject,
            }, data )

            :reject('no id recieved');
        });
    }

    return { analyze: async (data:optionValuation) => await subscribe(data) }
}