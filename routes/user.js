const express = require('express');
const app = express()
const wrapAsync = require('../utils/wrapAsync.js');
const router = express.Router();
const User = require("../models/user.js")
const flash = require("connect-flash")
app.use(flash())
const passport = require('passport');
const { saveRedirectUrl } = require('../middleware.js');
const userController = require('../controllers/user.js')


//signup routes
router.route("/signup")
.get(userController.renderSignupForm)
.post(wrapAsync(userController.userSignup))



//login routes
router.route("/login")
.get(userController.renderLoginForm)
.post(saveRedirectUrl, passport.authenticate(
    'local', {failureRedirect: "/login", failureFlash: true}
), wrapAsync(userController.userLogin))



//logout route
router.get("/logout", userController.userLogout);



module.exports = router;