//
//  ViewController.m
//  eMMaSampleApp-iOS
//
//  Created by Adrian on 14/12/15.
//  Copyright © 2015 eMMa. All rights reserved.
//

#import "ViewController.h"
#import "eMMa.h"

@interface ViewController ()

@property (weak, nonatomic) IBOutlet UISegmentedControl *genderSegment;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
}

-(void) viewDidAppear:(BOOL)animated {
    //Track event Page1
    [eMMa trackEvent:@"a1eeaf5c99b0321e3b28d72413e3a5be"];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (IBAction)goNext:(id)sender {

    NSString *genderResult = _genderSegment.selectedSegmentIndex == 0 ? @"Male" : @"Woman";
    
    [eMMa trackExtraUserInfo:@{
                               @"GENDER" : genderResult
                               }];
    
    /**
     * Track event Page2
     * This will be better on a new VC; But this is a sample, so this works
     */
    [eMMa trackEvent:@"c8ba0668ab5c55a709ea75da15883f3e"];
    
    [self performSegueWithIdentifier:@"ShowResult" sender:nil];
    
}

@end
