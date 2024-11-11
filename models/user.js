const mongoose = require('mongoose')
const Schema = mongoose.Schema

const passportLocalMongoose = require("passport-local-mongoose")

const userSchema = new Schema({

    email:{
        type: String,
        required: true
    }
});

userSchema.plugin(passportLocalMongoose)  //it will add username and password and perform hashing and salting too so that's why we do not need to store username and password in userSchema explicitely

module.exports = mongoose.model("User", userSchema);