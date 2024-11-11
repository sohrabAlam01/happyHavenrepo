if(process.env.NODE_ENV != "production") {

    require('dotenv').config();

}


const express = require('express');
const app = express();
const mongoose = require("mongoose");
const path = require("path");
const listingRouter = require('./routes/listing.js');
const reviewRouter = require("./routes/review.js");
const userRouter = require("./routes/user.js")
const expressError = require('./utils/expressError.js')
const methodOverride = require('method-override');
const flash = require('connect-flash');
const LocalStrategy = require('passport-local')
const passport = require('passport')
const User = require("./models/user.js")
//setting up ejs-mate. ejs-mate is basically used as the include 
const ejsMate = require('ejs-mate');
const { findById } = require('./models/review.js');
app.engine("ejs", ejsMate);
//setting up folder's path in which static files like css and js are written
app.use(express.static(__dirname + "/public"));  //we can also use: app.use(express.static)
//setting up ejs
app.set("view engine", "ejs");

app.set("views", __dirname + "/views");          //app.set("views", path.join(__dirname, "views")); since __dirname is a node.js variable that returns the address of the current directory in which the app.js is present
//to parse(encode) the url
app.use(express.urlencoded({ extended: true }));
app.use(methodOverride("_method"));


//creating and connecting database happyHaven (atlas mongodb)
const dbUrl = process.env.ATLASDB_URL
async function main() {
    await mongoose.connect(dbUrl); 
} 

main().then(() => { })
    .catch((err) => {
        console.log(err);
    })

//setting express-session
const session = require('express-session');
const MongoStore = require('connect-mongo');

const store = MongoStore.create({
    mongoUrl: dbUrl,
    crypto:{
        secret: process.env.SECRET
    },
    touchAfter: 24 * 3600
});

store.on("error", ()=>{
    console.log("ERROR IN MONGO SESSION STORE", err)
})

const sessionOptions = {
     store,
     secret :  process.env.SECRET,
     resave: false,
     saveUninitialized: true,

     cookie: {
              
        expires: Date.now() + 7*24*60*60*1000,        //login info will get expires after 7 days (given in milliseconds)
        maxAge : 7*24*60*60*1000,
        httpOnly: true,    //for security purpose
     }

};


app.use(session(sessionOptions));
app.use(flash());

app.use(passport.initialize())  //initializes passport for the current session
app.use(passport.session())
passport.use(new LocalStrategy(User.authenticate()));

passport.serializeUser(User.serializeUser());
passport.deserializeUser(User.deserializeUser());


//middleware to set flash message
app.use((req, res, next)=>{

    res.locals.successMsg = req.flash("success");
    res.locals.errorMsg = req.flash("error");
    res.locals.userInfo = req.user;  //req.user : it will be undefined when user is not logged in and contains user info when user is logged in
    next();
})



//listings route file
app.use('/listings', listingRouter);

//reviews routes file
app.use('/listings/:id/reviews', reviewRouter);

app.use("/", userRouter);



//default route: when none of the above route matches with the request then this route will be called by default that means not a valid request

app.all("*", (req, res, next)=>{
    next(new expressError(404, "Page not found!"));
})

 
//middleware to handle error for any route
app.use((err, req, res, next) => {
   // res.send("Something went wrong")  //it will take care of error at server side before saving the documents in the database like validation error, constraints etc
   let {statusCode = 500, message = "Something went wrong"} = err;
   res.status(statusCode).render("./Errors/error.ejs", {statusCode, message});
//    res.status(statusCode).send(message);
})




app.listen(8080, (req, res) => {
    console.log("i am listening");
})