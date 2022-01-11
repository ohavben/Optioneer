import { _RegularBonds_Type, _CVAIRS_Type, _ConvertibleBonds_Type, _CallableBonds_Type } from "./marketDataInterface"

type Prefix =  {
    dom: string;
    lowercase: string;
    css: string;
    js: string;
}

interface Subscription {
    id:string;
    resolve: (value: string | PromiseLike<string>) => void;
    reject:  (reason?: any) => void;
}

interface Subscriptions {
    //even though we specify the key to be of type number,
    // in run time it's a string like "675.4445646"
    children:Subscription;
}

export function debounce (fn: Function, ms: number) {
    let timeoutId: ReturnType<typeof setTimeout>;
    return function (this: any, ...args: any[]) {
        clearTimeout(timeoutId);
        timeoutId = setTimeout(() => fn.apply(this, args), ms);
    };
};

export function throttle(fn: Function, wait: number) {
    let inThrottle: boolean,
        lastFn: ReturnType<typeof setTimeout>,
        lastTime: number;
    return function (this: any) {
        const context = this,
        args = arguments;
        if (!inThrottle) {
            fn.apply(context, args);
            lastTime = Date.now();
            inThrottle = true;
        } else {
            clearTimeout(lastFn);
            lastFn = setTimeout(() => {
            if (Date.now() - lastTime >= wait) {
                    fn.apply(context, args);
                    lastTime = Date.now();
                }
            }, Math.max(wait - (Date.now() - lastTime), 0));
        }
    };
};

export function randomString(length:number, exception:string):string {
    var chars = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ';
    var result = '';
    for (var i = length; i > 0; --i) result += chars[Math.round(Math.random() * (chars.length - 1))];
    return (exception === result) ? randomString(length, exception) : result;
};

export const broweserPrefix = (() :Prefix =>  {

    let computedStyle:string = Object.values(window.getComputedStyle(document.documentElement)).join(''),
        pre = Prefix(computedStyle),
        dom = DomPrefix(pre);

    function Prefix(copmutedStylesValuesString:string){
        let result:RegExpMatchArray | null = copmutedStylesValuesString.match(/-(moz|webkit|ms)-/);
        return (!result)? '': result[1].toString()
    }

    function DomPrefix(prefix:string){
        let  dom:RegExpMatchArray | null = ('WebKit|Moz|MS|O').match(new RegExp('(' + prefix + ')', 'i'));
        return (!dom)? '': dom[1].toString()
    }
    
    return {
        dom: dom,
        lowercase: pre,
        css: '-' + pre + '-',
        js: pre[0].toUpperCase() + pre.substring(1)
      };
})();

export function indexOfSmallestInArray(array:[number]):number {
    var lowest = 0;
    for (var i = 1; i < array.length; i++) {
        if (array[i] < array[lowest]) lowest = i;
    }
    return lowest;
}

export function pricer (url:string){

    let subs = new Map(), pricer = new Worker(`${url}`, { type: 'module' });

    pricer.onmessage = workerListerner;

    pricer.onerror = (e => console.log("ERROR in worker: ", e))

    function workerListerner(event: { data: string }){
        console.log(event)
        console.log("SUBS: " , subs)
        //console.log("SUB: ", subs[key])
        let { data } =  event;
        let calaculationResponse = JSON.parse(data);
        let key = calaculationResponse.request.id.toString();
        let response = subs.get(key)
        console.log("looking for subscription: ", response)
        if (!response) {
            console.log(`no subsciption found for key ${key}`)
            return
        }
        response.resolve(data)
        subs.delete(key)
        return 
        /*console.log("SUB: ", subs[key])
        //console.log("worker recieved calculstion id: ", key, " for: ", subs[key])
        //, key = data.request.id.toString(), payload = JSON.stringify(data);
        //console.log("worker sent message: ", typeof data.request.id, ': ', data.request.id, data)
        //even though we specify the key to be of type number,
        // in run time it's a string like "675.4445646"
        if (!subs[key]) {
            console.log("no sub for this id: ", key , ": ", data)
            return
        } 
        subs[key].resolve(data)
        return delete subs[key]*/
    }

    function publish(sub:Subscription, data: _RegularBonds_Type | _CVAIRS_Type | _ConvertibleBonds_Type | _CallableBonds_Type){
        if (data.request.id){
            subs.set(data.request.id.toString(), sub)
            console.log("SUBS:", subs)
            //subs[data.request.id.toString()] = sub
            console.log("publishing data: " , data)
            return pricer.postMessage(JSON.stringify(data))
        } else {
            return sub.reject('no id sent')
        } 
    }

    function subscribe (data: _RegularBonds_Type | _CVAIRS_Type | _ConvertibleBonds_Type | _CallableBonds_Type):Promise<string> {
        return new Promise((resolve, reject) => {
            return (data.request.id)
            ?publish({
                id: data.request.id.toString(),
                resolve: resolve,
                reject: reject,
            }, data )

            :reject('no id recieved');
        });
    }

    return { analyze: async (data: _RegularBonds_Type | _CVAIRS_Type | _ConvertibleBonds_Type | _CallableBonds_Type ) => await subscribe(data) }
}



/*
Today’s Little Program isn’t even a program. It’s just a function.

The problem statement is as follows: Given a nonempty JavaScript array of numbers, find the index of the smallest value. (If the smallest value appears more than once, then any such index is acceptable.)

One solution is simply to do the operation manually, simulating how you would perform the operation with paper and pencil: You start by saying that the first element is the winner, and then you go through the rest of the elements. If the next element is smaller than the one you have, you declare that element the new provisional winner.

function indexOfSmallest(a) {
 var lowest = 0;
 for (var i = 1; i < a.length; i++) {
  if (a[i] < a[lowest]) lowest = i;
 }
 return lowest;
}
Another solution is to use the reduce intrinsic to run the loop, so you merely have to provide the business logic of the initial guess and the if statement.

function indexOfSmallest(a) {
 return a.reduce(function(lowest, next, index) {
                   return next < a[lowest] : index ? lowest; },
                 0);
}
A third solution is to use JavaScript intrinsics to find the smallest element and then convert the element to its index.

function indexOfSmallest(a) {
 return a.indexOf(Math.min.apply(Math, a));
}
https://devblogs.microsoft.com/oldnewthing/20140526-00/?p=903

*/