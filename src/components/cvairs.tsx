import React, { useState } from "react";
import { CVAIRS } from "../marketData"


function Cvairs(){
    const [color, setColor] = useState("");
    return (
        <footer>
            <h2>my footer</h2>
        </footer>
    )
}

export default Cvairs

/* import React, {useState, useEffect} from "react"

const ShowPosts = () => {
    const [posts, setPosts] = useState([]);
    
    useEffect( () => { 
        async function fetchData() {
            try {
                const res = await axios.get('/posts'); 
                setPosts(res.data);
            } catch (err) {
                console.log(err);
            }
        }
        fetchData();
    }, []);
    return <div>{posts}</div>
}*/