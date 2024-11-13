const express = require('express')
const router = express.Router();
const wrapAsync = require('../utils/wrapAsync.js')
const {isLoggedIn, isOwner, validateListing} = require("../middleware.js")
const listingController  = require('../controllers/listing.js')
const multer  = require('multer')
const {storage} = require('../cloudConfig.js')
const upload = multer({ storage });
const listing = require("../models/listing.js");


router.route("/")
.get(wrapAsync(listingController.index))   //index route : to show all listings
.post(isLoggedIn, upload.single('listing[image]'),  validateListing ,wrapAsync(listingController.createListing)); //create route: routr to save the entered listing info




//note: put new route above the show route bcs "/listings/:id" is confusing with "/listings/new" it's reading new as id
//new route: rout to render a form to create a new listing
router.get("/new",  isLoggedIn, listingController.renderNewForm)



router.route("/:id")
.get(wrapAsync(listingController.showListing))  //show route: to show an individual listing
.put(isLoggedIn, isOwner, upload.single('listing[image]'), validateListing, wrapAsync(listingController.updateListing))  //update route
.delete(isLoggedIn, isOwner,  wrapAsync(listingController.deleteListing)) //delete route



//edit route: route to render the edit form
router.get("/:id/edit", isLoggedIn, isOwner, wrapAsync(listingController.renderEditForm));


module.exports = router;