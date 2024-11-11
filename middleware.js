const Listing = require("./models/listing.js")
const Review = require("./models/review.js")
const { listingSchema, reviewSchema } = require("./joiSchemaValidator.js")
const expressError = require('./utils/expressError.js')

module.exports.isLoggedIn = (req, res, next)=> {

    
    if(!req.isAuthenticated()){

        req.session.redirectUrl = req.originalUrl;
        
        req.flash("error" , "Login to create listings");
        return res.redirect("/login");

    }

    next();

};


//since when login is done , passport reset the session object so in this case req.session.redirectUrl is lost so before executing login ,store the value of req.session.redirectUrl into locals

module.exports.saveRedirectUrl = (req, res, next)=>{

    if(req.session.redirectUrl){
         res.locals.redirectUrl = req.session.redirectUrl;
    }
    next();
};


module.exports.isOwner = async(req, res, next)=>{

    let { id } = req.params;
    
    let listing = await Listing.findById(id);
    if(!listing.owner.equals(res.locals.userInfo._id)){
        req.flash("error", "You do not have authorities to make changes")
        return  res.redirect(`/listings/${id}`);
    }

    next();

}

module.exports.isReviewAuthor = async(req, res, next)=>{

    let { id, reviewId } = req.params;
    
    let review = await Review.findById(reviewId);
    if(!review.author.equals(res.locals.userInfo._id)){
        req.flash("error", "You do not have authorities to make changes")
        return  res.redirect(`/listings/${id}`);
    }

    next();

}


module.exports.validateListing = (req, res, next)=>{
    let {error} = listingSchema.validate(req.body);
    if(error){
        let errMsg = error.details.map((el)=> el.message).join(",");
        throw new expressError(404, errMsg);
    }
    else{
        next();
    }
};

//function to validate review schema using joi
module.exports.validateReviewSchema = (req, res, next)=>{
    let {error} = reviewSchema.validate(req.body);
    if(error){
        let errMsg = error.details.map((el)=> el.message).join(",")
        throw new expressError(404, errMsg)
    }
    else{
        next()
    }
};

