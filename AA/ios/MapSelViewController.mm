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
    [self.view setFrame:CGRectMake(0,0, 480, 320)];
    UIImageView *background = [[UIImageView alloc]initWithImage:[UIImage imageNamed:@"popback.png"]];
    background.frame = CGRectMake(0,0, 480, 320);
    
    [self.view addSubview:background];
    [background release];
    
    [self.view setBackgroundColor:[UIColor blueColor]];
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
    if (_cur>2) {
        _cur=1;
    }
}
-(void)btnAction:(id)sel
{
        UIAlertView *alert =[[UIAlertView alloc]initWithTitle:@"提示" message:@"选择吗" delegate: self cancelButtonTitle:@"否" otherButtonTitles:@"是", nil];
        [alert show];
        [alert release];
}
-(void)backMain:(UIButton *)btn{
    XBridge::clearmy(true);
}
- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
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
//对画面进行单次点击时所触发的函式
-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    
    //宣告一个UITouch的指标来存放事件触发时所撷取到的状态
//    UITouch *touch = [[event allTouches] anyObject];
    
    //将XY轴的座标资讯正规化后输出
//    touchX.text = [NSString stringWithFormat:@"%0.0f", [touch locationInView:touch.view].x];
//    touchY.text = [NSString stringWithFormat:@"%0.0f", [touch locationInView:touch.view].y];
}
@end
