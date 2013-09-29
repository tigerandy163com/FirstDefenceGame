//
//  MapSelViewController.m
//  AA
//
//  Created by chunyu.wang on 13-9-28.
//
//

#import "MapSelViewController.h"
#import "InfiniteScrollPicker.h"
#import "XBridge.h"
@interface MapSelViewController ()

@end

@implementation MapSelViewController
@synthesize cur =_cur;
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    UIImageView *background = [[UIImageView alloc]initWithImage:[UIImage imageNamed:@"popback.png"]];
    background.frame = CGRectMake(0,0, 480, 320);
    
    [self.view addSubview:background];
    [background release];
    
    NSMutableArray *set1 = [[NSMutableArray alloc] init];
    for (int i = 1; i <= 6; i++) {
        [set1 addObject:[UIImage imageNamed:[NSString stringWithFormat:@"map%d.png", i]]];
    }
    
    InfiniteScrollPicker* isp = [[InfiniteScrollPicker alloc] initWithFrame:CGRectMake(0, 0, 480, 200)];
    [isp setItemSize:CGSizeMake(160, 160)];
    [isp setImageAry:set1];
    [self.view addSubview:isp];
    [set1 release];
    
    UIButton *btn = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [btn setTitle:@"就选他了" forState:UIControlStateNormal];
    [btn addTarget:self action: @selector(btnAction:) forControlEvents:UIControlEventTouchUpInside];
     
    [btn setFrame:CGRectMake(200, 200, 75, 30)];
    [self.view addSubview:btn];
    
    UIButton *back = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [back setTitle:@"back" forState:UIControlStateNormal];
    [back addTarget:self action:@selector(backMain:) forControlEvents:UIControlEventTouchUpInside];
    [back setFrame:CGRectMake(0, 0, 75, 30)];
    [self.view addSubview:back];

}
- (void)infiniteScrollPicker:(InfiniteScrollPicker *)infiniteScrollPicker didSelectAtImage:(NSNumber*)image
{
    NSLog(@"selected::%d",[image integerValue]);
    _cur = [image integerValue];
//    AppController *controller = (AppController *)[UIApplication sharedApplication ].delegate;
//    [controller setCutMap:[image integerValue]];
}
-(void)btnAction:(id)sel
{
        UIAlertView *alert =[[UIAlertView alloc]initWithTitle:@"提示" message:@"选择吗" delegate: self cancelButtonTitle:@"否" otherButtonTitles:@"是", nil];
        [alert show];
        [alert release];
}
-(void)backMain:(UIButton *)btn{
    XBridge::clearmy();
}
- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
- (BOOL) shouldAutorotateToInterfaceOrientation:
(UIInterfaceOrientation)toInterfaceOrientation {
    return (toInterfaceOrientation == UIInterfaceOrientationLandscapeRight);
}
- (NSUInteger)supportedInterfaceOrientations {
    return UIInterfaceOrientationMaskLandscapeRight;
}

- (void) alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex{
    //Code.....
    if (buttonIndex==0) {
 
    }else if (buttonIndex==1){
               XBridge::setCurMap(_cur);
        XBridge::startGameWithMap();
    }
}
@end
