const User = require('../models/user')


module.exports.userSignup = async(req, res)=>{

    try{
      
        let{username, email, password} = req.body;
        const newUser = new User({
            username,
             email
        });

        const registeredUser = await User.register(newUser, password);
        console.log(registeredUser);
        req.login(registeredUser, (err)=>{

            if(err) return next(err);
            req.flash("success", "Welcome to happyHaven");
            res.redirect("/listings");
        });

     }catch(e){
        req.flash("error", e.message)
        res.redirect("/signup");
    }
};

module.exports.renderSignupForm = (req, res)=>{

    res.render("users/signup.ejs");

};


module.exports.renderLoginForm = (req, res)=>{
    res.render("users/login.ejs");
};


module.exports.userLogin = async(req, res)=>{

    req.flash("success", "Welcome back to happyHaven")
    let redirectUrl = res.locals.redirectUrl || "/listings";  //when isLoggedIn middleware is not triggered then res.locals.redirectUrl will be empty
    res.redirect(redirectUrl);

};

module.exports.userLogout = (req, res, next)=>{
    
    req.logout( (err)=>{
       if(err) return next(err);
       req.flash("success", "Logged out! Thanks for visiting");
       res.redirect("/listings")
    });

};