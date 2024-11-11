const express = require('express')
const router = express.Router({mergeParams : true});
const Review = require("../models/review.js");
const wrapAsync = require('../utils/wrapAsync.js');
const Listing = require("../models/listing.js");
const {validateReviewSchema, isLoggedIn, isReviewAuthor, isOwner} = require("../middleware.js");
const reviewController = require('../controllers/review.js')






//Review post route
router.post("/", isLoggedIn, validateReviewSchema, wrapAsync(reviewController.postReview));


//Review delete route
router.delete("/:reviewId", isLoggedIn, isReviewAuthor, wrapAsync(reviewController.deleteReview));

module.exports = router;