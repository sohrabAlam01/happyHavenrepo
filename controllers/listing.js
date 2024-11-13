const Listing = require('../models/listing');
const mbxGeocoding = require('@mapbox/mapbox-sdk/services/geocoding');
const mapToken = process.env.MAP_TOKEN;
const geocodingClient = mbxGeocoding({ accessToken: mapToken });


module.exports.index = async (req, res, next) => {
    let allListings = await Listing.find({});
    res.render("listings/allListings.ejs", { allListings });
};

module.exports.renderNewForm = (req, res) => {

    res.render("listings/newListing.ejs");

};

module.exports.showListing = async (req, res, next) => {
    let { id } = req.params;
    let listing = await Listing.findById(id).populate({path: "reviews", populate: {path: "author"}}).populate("owner");
    console.log(listing);
    if(!listing){
        req.flash("error", "Listing does not exist");
        res.redirect("/listings"); 
    }else
    res.render("listings/show.ejs", { listing });
};

module.exports.createListing = async (req, res, next) => {
   
   const response = await geocodingClient.forwardGeocode({
        query: req.body.listing.location,
        limit: 1
      })
        .send()
        
   //console.log(response.body.features[0]);

    let url = req.file.path;
    let filename = req.file.filename;
   
    let newListing = new Listing(req.body.listing);
    newListing.owner = req.user._id;

    newListing.image = {url, filename};
    newListing.geometry = response.body.features[0].geometry; 
    
    await newListing.save();
    req.flash("success", "New listing created")
    res.redirect("/listings");

};

module.exports.renderEditForm = async (req, res, next) => {
    let { id } = req.params;
    let listing = await Listing.findById(id);
    if(!listing){
        req.flash("error", "Listing does not exist");
        res.redirect("/listings"); 
    }else{
       let originalImageUrl = listing.image.url;
       originalImageUrl =  originalImageUrl.replace("/upload", "/upload/w_350")
        res.render("listings/edit.ejs", { listing , originalImageUrl});
    }
    
};

module.exports.updateListing = async (req, res, next) => {
    let { id } = req.params;

    let listing = await Listing.findById(id);
    if(!listing.owner.equals(res.locals.userInfo._id)){
        req.flash("error", "You do not have authorities to make changes")
        return res.redirect(`/listings/${id}`);
    }

    let updatedListing = await Listing.findByIdAndUpdate(id, { ...req.body.listing });

    if(typeof req.file !== "undefined"){

    let url = req.file.path;
    let filename = req.file.filename;

    // console.log(req.body.listing);
    //  console.log(await Listing.findById(id));
   
    updatedListing.image = {url, filename};
    
    }
    await updatedListing.save();
    req.flash("success", "Listing updated successfully")
    res.redirect(`/listings/${id}`);
};

module.exports.deleteListing = async (req, res, next) => {
    let { id } = req.params;
    await Listing.findByIdAndDelete(id);
    req.flash("success", "Listing deleted successfully")
    res.redirect("/listings");
}