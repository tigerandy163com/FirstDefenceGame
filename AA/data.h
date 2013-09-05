//
//  data.h
//  AA
//
//  Created by chunyu.wang on 13-9-4.
//
//

#ifndef AA_data_h
#define AA_data_h

#define TowerMaxLevel 4
#define Tower1Cost 25
#define Tower2Cost 30
#define Tower3Cost 40
#define Tower4Cost 60

#define  T1Range  100
#define T2Range   150
#define T3Range   200
#define T4Range   200

#define T1Damage  10
#define T2Damage  10
#define T3Damage   30
#define T4Damage   20

#define T1MaxDamage  25
#define T2MaxDamage   25
#define T3MaxDamage    55
#define T4MaxDamage    45

#define T1Speed 0.5f
#define T2Speed  0.8f
#define T3Speed  0.8f
#define T4Speed  0.8f

#define T1Interval 0.5f
#define T2Interval 0.8f
#define T3Interval 0.8f
#define T4Interval 1.0f

#define EnemyTexture CCTextureCache::sharedTextureCache()->textureForKey("enemy.png")
#define Tower1_1  CCSpriteFrame::createWithTexture(EnemyTexture, CCRectMake(520, 156 ,40, 59))
#define Tower1_2  CCSpriteFrame::createWithTexture(EnemyTexture, CCRectMake(979, 189, 41, 57))
#define Tower1_3  CCSpriteFrame::createWithTexture(EnemyTexture, CCRectMake(468 ,238, 52, 61))
#define Tower1_4  CCSpriteFrame::createWithTexture(EnemyTexture, CCRectMake(248, 333, 61, 73))

#define Tower2_1  CCSpriteFrame::createWithTexture(EnemyTexture, CCRectMake(58, 225, 45, 62))
#define Tower2_2  CCSpriteFrame::createWithTexture(EnemyTexture, CCRectMake(0 ,307, 47 ,69))
#define Tower2_3  CCSpriteFrame::createWithTexture(EnemyTexture, CCRectMake(309, 333, 49, 77))
#define Tower2_4  CCSpriteFrame::createWithTexture(EnemyTexture, CCRectMake(358, 333, 51, 82))

#define Tower3_1  CCSpriteFrame::createWithTexture(EnemyTexture, CCRectMake(904, 366, 60, 55))
#define Tower3_2  CCSpriteFrame::createWithTexture(EnemyTexture, CCRectMake(964 ,372, 60, 58))
#define Tower3_3  CCSpriteFrame::createWithTexture(EnemyTexture, CCRectMake(718, 443, 60, 69))
#define Tower3_4  CCSpriteFrame::createWithTexture(EnemyTexture, CCRectMake(784, 422, 60, 90))

#define Tower4_1  CCSpriteFrame::createWithTexture(EnemyTexture, CCRectMake(409 ,333, 43, 62))
#define Tower4_2  CCSpriteFrame::createWithTexture(EnemyTexture, CCRectMake(0 ,376, 53 ,72))
#define Tower4_3  CCSpriteFrame::createWithTexture(EnemyTexture, CCRectMake(53, 393, 53, 83))
#define Tower4_4  CCSpriteFrame::createWithTexture(EnemyTexture, CCRectMake(106 ,393, 53 ,92))

//(134 Tower5_1 enemy 159 393 42 49)
//(135 Tower5_2 enemy 409 395 48 55)
//(136 Tower5_3 enemy 201 406 60 59)
//(137 Tower5_4 enemy 457 406 60 66)
//(138 Tower6_1 enemy 634 428 60 54)
//(139 Tower6_2 enemy 261 410 60 60)
//(140 Tower6_3 enemy 321 415 60 70)
//(141 Tower6_4 enemy 517 419 62 89)
//(142 Tower7_1 enemy 579 419 55 69)
//(143 Tower7_2 enemy 850 421 62 63)
//(144 Tower7_3 enemy 912 430 62 80)
//(145 Tower7_4 enemy 832 303 62 100)
#define ICONS CCTextureCache::sharedTextureCache()->textureForKey("icons.png")
//(148 ui_skill1_normal icon 0 0 50 50)
//(149 ui_skill1_press icon 50 0 50 50)
//(150 ui_skill2_normal icon 100 0 50 50)
//(151 ui_skill2_press icon 150 0 50 50)
//(152 ui_skill3_normal icon 200 0 50 50)
//(153 ui_skill3_press icon 0 50 50 50)
//(154 ui_tower1_normal icon 50 50 50 50)
//(155 ui_tower1_press icon 100 50 50 50)
//(156 ui_tower2_normal icon 150 50 50 50)
//(157 ui_tower2_press icon 200 50 50 50)
//(158 ui_tower3_normal icon 0 100 50 50)
//(159 ui_tower3_press icon 50 100 50 50)
//(160 ui_tower4_normal icon 100 100 50 50)
//(161 ui_tower4_press icon 150 100 50 50)
//(162 ui_tower5_normal icon 200 100 50 50)
//(163 ui_tower5_press icon 0 150 50 50)
//(164 ui_tower6_normal icon 50 150 50 50)
//(165 ui_tower6_press icon 100 150 50 50)
//(166 ui_tower7_normal icon 150 150 50 50)
//(167 ui_tower7_press icon 200 150 50 50)
//(168 ui_dot icon 0 200 11 9)
//(169 loading_bar4 icon 11 200 12 37)
//(170 ui_moneysign icon 23 200 13 23)
//(171 ui_Triangle_2 icon 36 200 14 16)
//(172 ui_Triangle icon 50 200 0 0)
//(173 Triangle icon 70 201 22 38)
//(174 ui_gold icon 94 202 25 25)
//(175 ui_menu icon 120 201 25 31)
//(176 achievements_locked icon 145 200 28 45)
//(177 achievements_opened icon 173 200 28 45)
//(178 ui_play icon 203 202 30 30)
//(179 ui_stop icon 38 220 30 30)
//(180 arrow1 icon 53 202 14 16)
#define TowerIcon1 CCSpriteFrame::createWithTexture(ICONS, CCRectMake(50 ,50 ,50 ,50))
#define TowerIcon2 CCSpriteFrame::createWithTexture(ICONS, CCRectMake(150 ,50 ,50 ,50))
#define TowerIcon3 CCSpriteFrame::createWithTexture(ICONS, CCRectMake(0 ,100 ,50 ,50))
#define TowerIcon4 CCSpriteFrame::createWithTexture(ICONS, CCRectMake(100 ,100 ,50 ,50))

#define ui_play CCSpriteFrame::createWithTexture(ICONS, CCRectMake(203, 202, 30 ,30))
#define ui_stop CCSpriteFrame::createWithTexture(ICONS, CCRectMake(38 ,220 ,30, 30))

#define ChooseTexture CCTextureCache::sharedTextureCache()->textureForKey("choose.png")
//(28 button_max_normal choose 812 344 52 59)
//(29 button_sell_normal choose 864 344 52 59)
//(30 button_upgrade_normal choose 916 344 52 59)
//21 ui_lv1_normal choose 390 343 60 60)
//(22 ui_lv1_press choose 450 344 60 60)
//(23 ui_lv2_normal choose 510 344 60 60)
//(24 ui_lv2_press choose 570 343 60 60)
#define button_max_normal CCSpriteFrame::createWithTexture(ChooseTexture, CCRectMake(812, 344, 52, 59))
#define button_sell_normal CCSpriteFrame::createWithTexture(ChooseTexture, CCRectMake(864, 344, 52, 59))
#define button_upgrade_normal CCSpriteFrame::createWithTexture(ChooseTexture, CCRectMake(916, 344, 52, 59))
#define ui_lv1_normal CCSpriteFrame::createWithTexture(ChooseTexture, CCRectMake(390, 343,60, 60))
#define ui_lv1_press CCSpriteFrame::createWithTexture(ChooseTexture, CCRectMake(450, 344 ,60, 60))
#define ui_lv2_normal CCSpriteFrame::createWithTexture(ChooseTexture, CCRectMake(510, 344, 60, 60))
#define ui_lv2_press CCSpriteFrame::createWithTexture(ChooseTexture, CCRectMake(570, 344, 60, 60))
#endif
