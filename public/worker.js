import Module from './quantlib.js';

self.onmessage = async ({ data } = evt) => 
    self.postMessage(
        await Module()
            .then(pricer => pricer[`${JSON.parse(data).request.name}`](data))
            .catch(e => console.log("ERROR IN WORKER: ", e))
    )
  
