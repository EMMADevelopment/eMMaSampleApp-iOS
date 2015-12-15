//
//  eMMa.h
//  eMMa_iOS_SDK
//
//  Created by Jaume Cornadó Panadés on 30/9/14.
//  Copyright (c) 2014 moddity. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class UIButton;
@class eMMaPushSystemController;

#import "eMMaDefines.h"


@interface eMMa : NSObject

///---------------------------------------------------------------------------------------
/// @name eMMa Initialization
///---------------------------------------------------------------------------------------

/**
Starts the session with our servers

You can get your App Key from your App info. Just go to My Account > Support and create your App (if you did not do it before) and get your App Key right there. Easy!
 
For a simple configuration put this in you AppDelegate's method:
    
 
    - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
        // Override point for customization after application launch.
 
        [eMMa starteMMaSession:@"MYFANCYAPPKEY"];
        [eMMa trackLocation];
        [eMMa startPushSystem];
        [eMMa checkForAdBall];
        [eMMa addRateAlertForAppStoreURL:@"https://itunes.apple.com/es/app/mygreatapp"];

        return YES;
    }
 
 @param appKey You app key
*/
+(void)starteMMaSession:(NSString*)appKey;


///---------------------------------------------------------------------------------------
/// @name eMMa Configuration
///---------------------------------------------------------------------------------------

/** Gets the current SDK Version */
+(NSString*)getSDKVersion;

/**
 If you need to see the eMMa log, enable it (before starteMMaSession)
 
 @param visible Enable log when true
 */
+(void)setDebuggerOutput:(BOOL)visible;

/**
 Enables eMMa to use the location of the user
 
 This method requieres NSLocationWhenInUseUsageDescription key defined into Info.plist file. If this key is not defined no location tracking will be enabled.
 */
+(void)trackLocation;

/**
 Configures eMMa Root View Controller. Useful to complex implementations
 
 By default eMMa uses the main window rootViewController.
 If this VC is an UINavigationController uses the first VC of the stack as the rootViewController.
 */
+(void)seteMMaRootViewController:(UIViewController*)viewController;

/**
 Enable or disable IDFA Tracking
 
    *IMPORTANT*
 
    IDFA tracking is enabled by default on eMMa. If you don’t want to track with IDFA please use method [eMMa setUseIDFA:BOOL]; in order to disable. 
    Anyway you need to check the speciefied box on iTunnes Connect question regarding IDFA tracking.
 
 @param use tells to eMMa when to use IDFA tracking. If NO VendorID will be used. It can be enabled/disabled for future app releases.
 */
+(void)setUseIDFA:(BOOL)use;


/** 
 * @name Tracking User Behaviour
 * 
 * With eMMa you can track everything. Here you’ll find the methods that allow tracking custom event that happens on your application and also log all page views.
 */

/**
 Use trackEvent to count the number of times certain events happen during a session of your application.
 
 This can be useful for measuring how often users perform various actions, for example. Your application is currently limited to counting occurrences for 30 different event ids.
 
    [eMMa trackEvent:@"EVENT_TOKEN"];
 
 You can get the EVENT_TOKENS creating events on eMMa web platform, if a non-existent token is sent eMMa will return error.
 
 @param event An event token obtained from eMMa Dashboard
 */
+(void)trackEvent:(NSString*)event;


///---------------------------------------------------------------------------------------
/// @name eMMa User Stats
///---------------------------------------------------------------------------------------

/**
 LoginUser logs the user on eMMa database for a user_id (NSString) and email (NSString). When logged you can use [eMMa loginDefault] for log another sign in for the user with the same data.
 
 @param userId the unique id of the user
 @param mail the mail of the user
 @param extras extra fields to track
 */
+(void)loginUserID:(NSString*)userId forMail:(NSString*)mail andExtras:(NSDictionary*)extras;

/**
 Convinence method equivalent to loginUserID:forMail:andExtras: without shipping extra fields
 */
+(void)loginUserID:(NSString*)userId forMail:(NSString*)mail;

/**
 Log the user with the default data
 */
+(void)loginDefault;

/**
 RegisterUser set a complete registration from device on eMMa database for a user_id (NSString) and email (NSString)
 
 @param userId unique user identifier
 @param mail the mail of the user
 @param extras extra fields to track
 */
+(void)registerUserID:(NSString*)userId forMail:(NSString*)mail andExtras:(NSDictionary*)extras;

/** Convinence method without extras, see: registerUserID:forMail:andExtras */
+(void)registerUserID:(NSString*)userId forMail:(NSString*)mail;

/**
 This method update or add extra parameters for current logged user in order to have a better segmentation data. It can be used anywhere.
 
    Example of usage:
 
    NSDictionary *extras = @{ @"key1" : @"value1", @"key2" : @"value2" };
    [eMMa trackExtraUserInfo: extras];
 
 @param info This method sends key/value information to track on the user
 */
+(void)trackExtraUserInfo:(NSDictionary*)info;

///---------------------------------------------------------------------------------------
/// @name Tracking Purchase for mCommerce
///---------------------------------------------------------------------------------------

/**
 Starts an order for adding products
 
 @param orderId your order id
 @param customerId your Customer ID. If not passed, eMMa will use the logged one (if exists).
 @param totalPrice your total price
 @param coupon your coupon if needed.
 @param extras extra parameters to track (category, etc...)
 */
+(void)startOrder:(NSString*)orderId customerId:(NSString*)customerId totalPrice:(float)totalPrice coupon:(NSString*)coupon extras:(NSDictionary*)extras;

/**
 Conveinence method without extras. See startOrder:customerId:totalPrice:coupon:extras
 */
+(void)startOrder:(NSString*)orderId customerId:(NSString*)customerId totalPrice:(float)totalPrice coupon:(NSString*)coupon;

/**
 Adds products to your current started order. Always startOrder should be called before.
 
 @param productId your product id.
 @param name your product name
 @param qty your product qty
 @param price product price
 @param extras extra parameters to track
 */
+(void)addProduct:(NSString*)productId name:(NSString*)name qty:(float)qty price:(float)price extras:(NSDictionary*)extras;

/**
 Convinence method without extras. See: addProduct:productId:name:qty:price:extras:
 */
+(void)addProduct:(NSString*)productId name:(NSString*)name qty:(float)qty price:(float)price;

/**
 Track the current order. It should be called after startOrder and after being all cart products added.
 
 The sequence of tracking order in eMMa is always startOrder>addProduct(*distinct products)>trackOrder
 */
+(void)trackOrder;

/** Sets the current currency code for the orders */
+(void)setCurrencyCode:(NSString*)currencyCode;

/**
 Cancel the order referenced by an order id. If your e-commerce allows canceling orders this method updates the purchases data with the cancelled orders.
 */
+(void)cancelOrder:(NSString*)orderId;

///---------------------------------------------------------------------------------------
/// @name eMMa Start View
///---------------------------------------------------------------------------------------

/**
 Sets the current startView options
 
 Options:
    eMMaStartViewManualCall -> Sets the startView in manual mode. Useful for using startviews with labels.
                                Also disables check for startview returning from background
 
 @param options all the options for the startview
 */
+(void) setStartViewOptions: (eMMaStartViewOptions) options;

/**
 *  Sets the delegate for the StartView actions. This will be called when the user interacts with the StartView
 *
 *  @param delegate delegate
 */
+(void) setStartViewDelegate:(id<eMMaStartViewDelegate>) delegate;


/**
 *  If you want you can pass a NSDictionary of parameters (key-value pair) that will append to the URL as a GET parameters. This is useful in case that you need to pass some data from the app to a StartView with a landing page.
 *
 *  @param parameters NSDictionary of parameters
 */
+(void) setStartViewParameters:(NSDictionary*) parameters;

/**
 Use checkForStartViewWithLabel in order to check if show Promotion web views added on eMMa dashboard. If you want you can pass a custom NSString that labels the StartView in case you use more than one StartViews on your app and you need to distinguish between them. NOTE: You cannot use autocreation parameter using label because labeled Startviews are attached to a specific part of the app, not at the startup.
 */
+(void) checkForStartViewWithLabel: (NSString*) label;

/**
 *  Closes the current StartView
 */
+(void) closeStartView;

///---------------------------------------------------------------------------------------
/// @name eMMa AdBall
///---------------------------------------------------------------------------------------

/**
 Use checkForAdBall in order to check if show AdBalls added on eMMa dashboard.
 */
+(void) checkForAdBall;

/**
 AdBall configuration options
 
 eMMaAdBallNotInBackground -> Don't check adball on return of background
 
 @param options bitmask of options
 */
+(void) setAdBallOptions: (eMMaAdBallOptions) options;

/**
 Use checkForAdBall in order to check if show AdBalls added on eMMa dashboard. If you want you can pass a custom NSString that labels the AdBall in case you use more than one AdBalls on your app and you need to distinguish between them. 
 
 @param label Label to check the adball
 */
+(void) checkForAdBallWithLabel: (NSString*) label;

///---------------------------------------------------------------------------------------
/// @name eMMa Banner
///---------------------------------------------------------------------------------------

/**
 *  Use checkForBannerOnViewcontroller in order to check if show Banner added on eMMa dashboard.
 *
 *  @param viewController the UIViewController where the banner will be seen
 */
+ (void)checkForBannerOnViewController:(UIViewController*)viewController;

/**
 *   Use checkForBannerOnViewcontroller in order to check if show Banner added on eMMa dashboard. If you want you can pass a custom NSString that labels the Banner in case you use more than one Banner on your app and you need to distinguish between them.
 *
 *  @param viewController the UIViewController where the banner will be seen
 *  @param label          the label you assigned on eMMa for the Banner
 */
+ (void)checkForBannerOnViewcontroller:(UIViewController*)viewController withLabel:(NSString*) label;

/**
 *  Sets the parameter to autocreate the Banner when coming from background
 *
 *  @param autoCreation if YES, it will create the Banner when coming from background automatically
 */
+(void) setBannerAutoCreation:(BOOL) autoCreation;


///---------------------------------------------------------------------------------------
/// @name eMMa Strip
///---------------------------------------------------------------------------------------


/**
 *  Use checkForStrip in order to check if show Strip added on eMMa dashboard.
 */
+ (void)checkForStrip;

/**
 *  Use checkForStripWithLabel in order to check if show Strip added on eMMa dashboard. If you want you can pass a custom NSString that labels the Strip in case you use more than one Strip on your app and you need to distinguish between them.
 *
 *  @param label the label you assigned on eMMa for the Strip
 */
+ (void)checkForStripWithLabel:(NSString*)label;

/**
 *  Sets the parameter to autocreate the Strip when coming from background
 *
 *  @param autoCreation if YES, it will create the Strip when coming from background automatically
 */
+ (void)setStripAutoCreation:(BOOL) autoCreation;


 ///---------------------------------------------------------------------------------------
/// @name eMMa Coupons
///---------------------------------------------------------------------------------------

+ (void)checkForCoupons:(eMMaGetCouponsBlock) response;

+ (void)checkForCouponsWithLabel:(NSString*)label result:(eMMaGetCouponsBlock) response;

+ (void)getCoupon:(NSInteger) couponId result:(eMMaGetCouponsBlock) response;

+ (void)redeemCoupon:(NSInteger) couponId;

+ (void)getCouponValidRedeems:(NSInteger)couponId result: (eMMaGetCouponsBlock)response;

+ (void)cancelCouponRedeem:(NSInteger)couponId count:(NSInteger)count;

+ (void)cancelCouponRedeem:(NSInteger)couponId;



 
///---------------------------------------------------------------------------------------
/// @name eMMa Tab Bar View
///---------------------------------------------------------------------------------------
/**
 Sets the UITabBarController where the DynamicTab will be shown. If no UITabBarController is defined, application won't execute
 
 @param tabBarController The Application UITabBarController
 */
+(void) setPromoTabBarController:(UITabBarController*)tabBarController;

/**
 *  Sets the index where the Dynamic Tab will be shown if it's not defined on eMMa Platform
 *
 *  @param index position where to show the DynamicTab
 */
+(void) setPromoTabBarIndex:(NSInteger) index;

/**
 *  Sets the UITabBarItem to show if it's not defined on eMMa Platform
 *
 *  @param tabBarItem the tabBarItem to show
 */
+(void) setPromoTabBarItem:(UITabBarItem*) tabBarItem;

/**
 *  Sets the parameter to autocreate the TabBar when coming from background
 *
 *  @param autoCreation if YES, it will create the DynamicTab when coming from background automatically
 */
+(void) setPromoTabBarAutoCreation:(BOOL) autoCreation;

/**
 *  Checks for DynamicTab on eMMa Platform
 */
+(void) checkPromoOnTabBar;

///---------------------------------------------------------------------------------------
/// @name eMMa Rate Alert
///---------------------------------------------------------------------------------------

/**
 Shedules an alert to rate the app
 
 eMMa makes easier to add a Rate alert in order to achieve more positive reviews app.
 
 @param appStoreURL Your AppStore app URL.
 */
+(void)addRateAlertForAppStoreURL:(NSString*)appStoreURL;

/**
 Frequency specifiying hours between alert shows
 
 By default 72 hours.
 
 @param hours  Int specifying hours between alert shows.
 */
+(void) setRateAlertFreq: (int) hours;

/**
 Configures the alert title.
 
 The default value is _Rate this app_
 
 @param title The alert title
 */
+(void) setRateAlertTitle: (NSString*) title;

/**
 Configures the alert message
 
 The default value is _If you like our app, please rate it on App Store!_
 
 @param message The alert message
 */
+(void) setRateAlertMessage: (NSString*) message;

/**
 Sets the cancel button caption
 
 The default value is _No, thanks_
 
 @param cancelButtonText The cancel caption
 */
+(void) setRateAlertCancelButton: (NSString*) cancelButtonText;

/**
 Sets the Rate Button caption
 
 The default value is _Rate it now!_
 
 @param rateItButtonText the rate button caption
 */
+(void) setRateAlertRateItButton: (NSString*) rateItButtonText;

/**
 Sets the Later button caption
 
 The default value is _Later_
 
 @param laterButtonText Later button caption
 */
+(void) setRateAlertLaterButton: (NSString*) laterButtonText;

/**
 *  Sets if the Alert must be shown after an App Update
    Default Value is NO
 *
 *  @param showAlert BOOL
 */
+(void) setRateAlertShowAfterUpdate:(BOOL) showAlert;

///---------------------------------------------------------------------------------------
/// @name eMMa Push system
///---------------------------------------------------------------------------------------

/**
 eMMa allows you to add a very powerful push system easy to integrate. Also allows you send info through pushes and do whatever you want inside your app with it. You need to generate your certificates for your app to be compatible with the push system. Please refer to Appendix Push Notification Certificates.
 
 @param launchOptions pass the launch options on the appdelegate's didFinishLaunching method
 */
+(void) startPushSystem: (NSDictionary*) launchOptions;

/**
 This method allows to configure the behaviour of the push system.
 
 Currently the supported options are:
 eMMaPushSystemDisableAlert -> Disables showing alert messages for new pushs received.
 */
+(void) setPushSystemOptions: (eMMaPushSystemOptions) options;

/**
 Configures the delegate for push handling
 
 @param delegate The delegate object
 */
+(void) setPushSystemDelegate: (id<eMMaPushDelegate>)delegate;

/**
 This method handles the remote notification payload
 
 
 Example of implementation:
 
    - (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo {
        [eMMa handlePush:userInfo];
    }
 
 @param userInfo The userInfo payload
 */
+(void) handlePush: (NSDictionary*) userInfo;

/**
 This method registers a new token on eMMa servers.
 
 
 Example of implementation:
 
    -(void) application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
    [eMMa registerToken:deviceToken];
    }
 
 @param deviceToken The token received from Apple Servers.
 */
+(void)registerToken:(NSData*)deviceToken;

/**
 Checks if eMMa had received any push tag in the current session
 
    eMMaPushTagBlock definition:
 
    typedef void(^eMMaPushTagBlock)(NSString* pushTag, NSString* pushTagID);
 
 @param pushTag the pattern of the pushtag to be checked
 @param block the block to be executed on pushtag received
 */
+(void) checkPushTag: (NSString*) pushTag withBlock: (eMMaPushTagBlock) block;

/**
 This method is replaced by handlePush: and will be removed from future releases
 */
+(void)checkReceivedNotifications:(NSDictionary *)options __deprecated;


///---------------------------------------------------------------------------------------
/// @name eMMa User Info
///---------------------------------------------------------------------------------------

+(void)getUserInfo:(eMMaGetUserInfoBlock) resultBlock;

+(void)getUserId:(eMMaGetUserIdBlock) resultBlock;

///---------------------------------------------------------------------------------------
/// @name eMMa Web SDK Sync
///---------------------------------------------------------------------------------------

/**
 *  This method syncs with eMMa Web SDK
 */
+(void)syncWithWebSDK;

/**
 *  This method, sets the domain where the webApp is hosted without the (http://)
 *  Ex: www.example.com
 *
 *  @param url URL without the http://
 */
+(void)setWebSDKDomain:(NSString*) domain;


/**
 * Returns if session is started and running
 *
 * @return true if started
 */
+(BOOL) isSessionStarted;


@end
