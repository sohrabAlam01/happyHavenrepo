 const joi = require('joi')

module.exports.listingSchema = joi.object({
    listing: joi.object({                         //there must be a listing oblject in listingSchema and in the listing object there must be the mentioned fields                     
        title: joi.string().required(),
        description: joi.string().required(),
        image: joi.string().allow("", null),
        price: joi.number().required(),
        location: joi.string().required(),
        country: joi.string().required(),
    }).required()
});


module.exports.reviewSchema = joi.object({
    review: joi.object({
        rating: joi.number().required().min(1).max(5),
        comment: joi.string().required()
    }).required()
})
