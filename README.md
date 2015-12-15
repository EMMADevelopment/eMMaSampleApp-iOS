# eMMa Sample App
This app has been tested in Xcode 7.

## Getting started

To use this app you need contact with info@emma.io previously, our Expert Service Department say you all metrics for run this app.

Metrics that you must be used:

- eMMa session key, necessary to establish a session with eMMa.

If you want to enable Push Notifications, you must upload the APNs certificates in eMMa Dashboard. Inside *My Account* you can upload development and production certificates (more info [eMMa certificates support](http://support.emma.io/hc/en-us/articles/203189022-iOS-push-certificates)).

## Integrating eMMa

### Add library to your Xcode project

First time you should drag the binary (*eMMa-Universal-static.a*) and headers (*eMMa.h* and *eMMaDefines.h*) to your Xcode project. You can create a group called eMMa SDK inside Frameworks directory.

![Xcode project folder](http://s8.postimg.org/smr59o0qt/Captura_de_pantalla_2015_12_15_a_les_15_52_42.png)

Add the following frameworks in Project if your app is iOS 7.0+:

- CoreLocation.framework
- AdSupport.framework

If you are using XCode7 to compile your app with iOS9, add App Transport Security and active NSAllowsArbitraryLoads in the Info.plis, in otherwise the app only support https url's.

  ```xml
  <key>NSAppTransportSecurity</key>
    <dict>
      <key>NSAllowsArbitraryLoads</key>
      <true/>
    </dict>
  ```
In the project (Build Settings, Build Options), disable BITCODE (ENABLE_BITCODE = NO).
If you have problems running this lib you should delete all weak-links to libs. Also in Other Linker Flags, you should set the options -ObjC -all_load.

### Start session with eMMa

eMMa needs start session in AppDelegate.m:

  ```obj-c  
  #import "AppDelegate.h"
  #import "eMMa.h"

  ...

  - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

      //init session in eMMa
      [eMMa starteMMaSession:@"emmasampleappJ2KIPmSms"];

      ...

      return YES;
  }
  ```
You can enable the debug mode, before the start session (not enable by default):

  ```obj-c
    [eMMa setDebuggerOutput: YES];
  ```

### Using Push Notifications

To receive Push in your app, you have to put the next methods in AppDelegate.m, after the session initialization:

  ```obj-c  
  - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {

     ...

    /enable/disable alert
    [eMMa setPushSystemOptions:eMMaPushSystemDisableAlert];

    //enable push
    [eMMa startPushSystem:launchOptions];

    return YES;
  }
  ```

  *setPushSystemOptions* allows enable/disable a native alert when notification arrives to device. This alert shows the text of message.
  *startPushSystem* initializes internally the Push system. It allows easy management.

  Also you must add the next methods:

  ```obj-c

  -(void) application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
      [eMMa registerToken:deviceToken];
  }

  - (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo {
      [eMMa handlePush:userInfo];
  }

  //If the iOS version is iOS 8 or later
  #ifdef __IPHONE_8_0
  - (void)application:(UIApplication *)application didRegisterUserNotificationSettings:(UIUserNotificationSettings *)notificationSettings
  {
      //register to receive notifications
      [application registerForRemoteNotifications];
  }

  -(void)application:(UIApplication *)application didFailToRegisterForRemoteNotificationsWithError:(NSError *)error {
      NSLog(@"Error: %@", error);
  }

  - (void)application:(UIApplication *)application handleActionWithIdentifier:(NSString *)identifier forRemoteNotification:(NSDictionary *)userInfo completionHandler:(void(^)())completionHandler
  {
      //handle the actions
      if ([identifier isEqualToString:@"declineAction"]){
      }
      else if ([identifier isEqualToString:@"answerAction"]){
      }
  }
  #endif
  ```
#### Optional

You can use two methods if you want to control what you receive from Push. In AppDelegate.h declares the delegate:

  ```obj-c
  @interface AppDelegate : UIResponder <UIApplicationDelegate, eMMaPushDelegate>

  @property (strong, nonatomic) UIWindow *window;

  @end

  ```
Next, add the next methods to AppDelegate.m:

  ```obj-c
    -(void)pushTag:(NSString*)pushTag{
      ...
    }

    -(void)pushMessage:(NSString*)pushMessage{
      ...
    }
```

*pushTag* sends the PushTag to the delegate when a Push is received. PushTag is optional in eMMa dashboard (Push panel).
*pushMessage* sends the message to the delegate when a Push is received.
