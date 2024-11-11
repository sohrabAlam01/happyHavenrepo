const mongoose = require('mongoose')
const initData = require("./data.js")
const Listing = require("../models/listing.js")

async function main(){
   await mongoose.connect('mongodb://127.0.0.1:27017/happyhaven');
}


main().then(()=>{
    console.log("connected to DB");
}).catch((err)=>{
    console.log(err);
});

//function to initialize database after deleting all existing documents
async function initDB(){

   await Listing.deleteMany({});
   initData.data = initData.data.map((obj)=> ({...obj , owner: "672f51d81c51c538b6819028" }));
   await Listing.insertMany(initData.data);
   console.log("data is initialized")
}

initDB();