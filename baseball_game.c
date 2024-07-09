#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int GetRandom(int min, int max);

//バッティング
int batting(int a ,int b ,int c, int d, int e, int f, int g,int h){
    int A = 0;   //A = 0でアウト,A >= 1で安打
    int ba, P1, P2;

    if(a == 0 && b == 0 && c == 0 && d == 0 && e == 0 && f == 0 && g == 0 && h == 0){
        A = -1;
        return A;
    }
    ba = b*1200 / (e + f + h ); //ミートとピッチャー能力でバットに当たる確率っぽいやつ
    P1 = GetRandom(1,1000);
    P2 = GetRandom(1,120);

    
    if (ba > P1){ 
        if (P2 < 30 - c/9){   
            A = 1;
        }else if(P2 < 90){
            A = 2;
        }else if(P2 < 98 + c/9){
            A = 4;
        }else if(P2 > 120 -d/9){
            A = 3;
        }
    }
    return A; //バッティングの結果を返す
}
//盗塁
int stolen_base(int a, int b){
    int P = GetRandom(1,100);
    int runner, A;
    if(a < b){
        A = 0;
    }else{
        runner = (a-b)*7;
        if(runner < P){
            A = 1;
        }else{
            A = 0;
        }
        return A;
    }
    
}
//バント
int bunt(int a,int b, int c){
    int A,P,batter;
    P = GetRandom(1,100);
    batter = a - (b + c)/13;
    if(batter < 0){
        A = 0;
    }else{
        if (batter * 3 + 30 > P){
            A = 1;
        }else{
            A = 0;
        }
    }
    return A;
}

//乱数生成
int GetRandom(int min, int max){
    srand((unsigned int)time(NULL));
    return min + (int)(rand() * (max - min + 1.0)/(1.0 + RAND_MAX));
}


int main(){
    int o = 1, times = 1, t, runner = 0, A_order = 0, B_order = 0, B_P = 0;
    int batting_result;
    int A[9]= {0,0,0,0,0,0,0,0,0}, B[9]= {0,0,0,0,0,0,0,0,0};
    int A_H = 0, B_H = 0, A_R = 0, B_R = 0;
    int i, j, command, start = 2;
    /******************************************************************************************* 
    選手パラメータをあんま意味なさそうだけど二次元配列に代入するとこ

    Aチーム:CPU  Bチーム:Player

    batter[7]={弾道,ミート,パワー,走力,肩力,捕球,守備力}
    picher[4]={球速,コントロール,スタミナ,変化球}
    *******************************************************************************************/
    int B_batter[9][7]={{2,70,60,96,63,61,41},
                        {3,78,74,64,74,67,62},
                        {4,90,95,78,85,42,52},
                        {4,75,92,64,61,59,55},
                        {4,82,73,57,39,47,54},
                        {4,80,76,47,60,59,71},
                        {3,92,72,81,65,76,78},
                        {2,85,70,56,82,66,74},
                        {2,78,75,86,67,89,77}};

    int B_pitcher[4][4]={{152,71,68,72},{152,59,74,80},{159,54,51,80},{163,44,80,80}};

    int A_batter[9][7]={{2,88,68,91,85,88,69},
                        {3,73,72,71,68,50,65},
                        {3,85,68,78,64,75,69},
                        {3,50,72,54,88,75,38},
                        {3,79,85,51,55,55,52},
                        {3,87,61,59,60,55,62},
                        {4,75,75,52,58,49,60},
                        {3,71,60,70,73,70,77},
                        {3,55,49,84,53,75,67}};

    int A_pitcher[4]={157,80,84,90};

    /***************************************************************************************** 
    *****************************************************************************************/

    while (start == 2 || start == 3){
        system("clear");
        printf("\n\n");
        printf("**************  やきう  ****************\n\n");
        printf("1 CF 周西                     1 RF 鈴木\n\n");

        printf("2 RF 遠藤                     2 SS 外島\n\n");

        printf("3 DH 小谷                     3 CF 赤木\n\n");

        printf("4 3B 村下                     4 C  城鳥\n");
        printf("             1,ゲーム開始\n");
        printf("5 LF 吉畑                     5 1B 大笠原\n");
        printf("             2,ゲーム説明\n");
        printf("6 1B 岡木                     6 LF 内山\n");
        printf("             3,選手能力確認\n");
        printf("7 2B 山畑                     7 DH 柿原\n");
        printf("             4,やめる      \n");
        printf("8 SS 源畑                     8 2B 石村\n\n");

        printf("9 C  中町                     9 3B 両岡\n\n");

        printf("  P  過去永                     P  ダッル\n");

        scanf("%d",&start);

        if(start == 1){system("clear");}

        if(start == 2){

            system("clear");

            printf("\n\n\n\n");
            printf("このゲームはかなりガバガバなコマンド野球ゲームです。\n\n");
            printf("まず,あなたが操作するのは後攻のBチームです\n");
            printf("コマンドの説明をしましょう\n\n\n");
            printf("ピッチャーに指示を出してください。\n");
            printf("********************\n");
            printf("1,任せる\n2,三振狙い\n3,打たせて取る\n4,全力投球\n5,ピッチャー交代\n");
            printf("********************\n\n\n");
            printf("これは守備時のコマンド入力画面です。\n\n");
            printf("1は選手に任せます。\n\n");
            printf("2は選手に三振を狙ってもらいます。(球速と変化球のパラメータが上がり、コントロールのパラメータが下がります。)\n\n");
            printf("3は打たせて取ります。(球速のパラメータが下がりコントロールと変化球のパラメータが上がります。)\n\n");
            printf("4は全力投球をします。(すべてのパラメータが上昇しますが体力を普段よりも消耗します。)\n\n");
            printf("5はピッチャー交代をさせます。\x1b[4m ピッチャーの体力が20を切ると能力が大幅に減ります。\x1b[0m 気を付けてください。\n\n\n");
            printf("適当な数字を入力して次に進んでください");
            scanf("%d",&i);
            system("clear");
            printf("\n\n\n\n\n\n\n\n");
            printf("バッターに指示を出してください。\n");
            printf("********************\n");
            printf("1,任せる\n2,長打狙い\n3,ヒット狙い\n4,バント\n5,盗塁\n6,代打\n");
            printf("********************\n\n\n");
            printf("これは攻撃時のコマンド入力画面です。\n\n");
            printf("1は選手にまかせます。\n\n");
            printf("2は長打を狙います(パワーのパラメータが上がり、ミートのパラメータが下がります。)\n\n");
            printf("3はヒットを狙います(ミートのパラメータが上がり、パワーのパラメータが下がります。)\n\n");
            printf("4はバントをします。成功しないこともあります。\n\n");
            printf("5は盗塁をします。無茶な場面で盗塁しようとすると断られます。\n\n");
            printf("適当な数字を入力して次に進んでください");
            scanf("%d",&i);
            system("clear");
            printf("\n\n\n\n");
            printf("------------------------------\n");
            printf("            [#]  \n\n\n\n\n");
            printf("[]                     [#]\n\n\n\n\n");
            printf("            < > 1アウト  \n");
            printf("------------------------------\n\n\n");
            printf("これは走者がどこの塁にいるかわかりやすくしたものです\n\n");
            printf("たとえば,[#]はその塁にランナーがいることを意味し,[]はその塁にランナーがいないことを意味します\n\n");
            printf("<>はホームベースのつもりです。");
            printf("なので、上の図は1アウト、ランナー1,2塁を表しています。\n\n");
            printf("このゲームにはストライクかボールかは存在しません。プロ入クオリティです。\n\n");
            printf("このゲームはsrandに現在の時刻を入れているので短時間にコマンドを連打すると同じ結果しか返ってきません。\n\x1b[4m 必ず1秒以上間をあけてコマンドを実行してください。\x1b[0m\n\n\n");
            printf("基本的な解説は以上です。選手能力を確認しておくのをお勧めします。\n\n\n");

        

            printf("適当な数を入力して次に進んでください。");
            scanf("%d",&i);
        }

        if(start == 3){
            system("clear");
            printf("\n\n");
            printf("選手能力確認");
            printf("野手\n\n");
            printf("            弾  ミ  パ  走  肩  捕  守\n\n");
            printf("1 CF 周西   %d  %d  %d  %d  %d  %d  %d\n\n",B_batter[0][0],B_batter[0][1],B_batter[0][2],B_batter[0][3],B_batter[0][4],B_batter[0][5],B_batter[0][6]);
            printf("2 RF 遠藤   %d  %d  %d  %d  %d  %d  %d\n\n",B_batter[1][0],B_batter[1][1],B_batter[1][2],B_batter[1][3],B_batter[1][4],B_batter[1][5],B_batter[1][6]);
            printf("3 DH 小谷   %d  %d  %d  %d  %d  %d  %d\n\n",B_batter[2][0],B_batter[2][1],B_batter[2][2],B_batter[2][3],B_batter[2][4],B_batter[2][5],B_batter[2][6]);
            printf("4 3B 村下   %d  %d  %d  %d  %d  %d  %d\n\n",B_batter[3][0],B_batter[3][1],B_batter[3][2],B_batter[3][3],B_batter[3][4],B_batter[3][5],B_batter[3][6]);
            printf("5 LF 吉畑   %d  %d  %d  %d  %d  %d  %d\n\n",B_batter[4][0],B_batter[4][1],B_batter[4][2],B_batter[4][3],B_batter[4][4],B_batter[4][5],B_batter[4][6]);
            printf("6 1B 岡木   %d  %d  %d  %d  %d  %d  %d\n\n",B_batter[5][0],B_batter[5][1],B_batter[5][2],B_batter[5][3],B_batter[5][4],B_batter[5][5],B_batter[5][6]);
            printf("7 2B 山畑   %d  %d  %d  %d  %d  %d  %d\n\n",B_batter[6][0],B_batter[6][1],B_batter[6][2],B_batter[6][3],B_batter[6][4],B_batter[6][5],B_batter[6][6]);
            printf("8 SS 源畑   %d  %d  %d  %d  %d  %d  %d\n\n",B_batter[7][0],B_batter[7][1],B_batter[7][2],B_batter[7][3],B_batter[7][4],B_batter[7][5],B_batter[7][6]);
            printf("9 C  中町   %d  %d  %d  %d  %d  %d  %d\n\n",B_batter[8][0],B_batter[8][1],B_batter[8][2],B_batter[8][3],B_batter[8][4],B_batter[8][5],B_batter[8][6]);

            printf("             速  コン 体  変\n\n");
            printf("10 P 過去永  %d  %d  %d  %d\n\n",B_pitcher[0][0],B_pitcher[0][1],B_pitcher[0][2],B_pitcher[0][3]);
            printf("11 P 戸卿    %d  %d  %d  %d\n\n",B_pitcher[1][0],B_pitcher[1][1],B_pitcher[1][2],B_pitcher[1][3]);
            printf("12 P 小勢    %d  %d  %d  %d\n\n",B_pitcher[2][0],B_pitcher[2][1],B_pitcher[2][2],B_pitcher[2][3]);
            printf("13 P 小谷    %d  %d  %d  %d\n\n",B_pitcher[3][0],B_pitcher[3][1],B_pitcher[3][2],B_pitcher[3][3]);
            
            printf("適当な数を入力して次に進んでください。");
            scanf("%d",&i);
            
        }

        if(start == 4){
            return 0;
        }
    }
    i = 0;
    
    //ゲーム開始  (times は裏表合わせた数,そのほうが何かと都合がいい)
    while (times <= 18){  

        if(times == 1){
            t = 0;
            printf("%d回表\n",t + 1);
        }else if(times % 2 == 0){
            t = times / 2 - 1;
            printf("%d回ウラ\n",t + 1);
        }else if(times % 2 == 1){
            t = times / 2 ;
            printf("%d回表\n",t + 1);
        }

        if(times % 2 == 1){
            printf("あなたは守備側です。");
        }else{
            printf("あなたは攻撃側です。");
        }

        for(o = 0, runner = 0; o < 3;){

//***********************************************************************************************
//************ 表 *******************************************************************************
            if(times % 2 == 1){
                
                printf("ピッチャーに指示を出してください。\n");
                printf("********************\n");
                printf("1,任せる\n2,三振狙い\n3,打たせて取る\n4,全力投球\n5,ピッチャー交代\n");
                printf("********************\n");
                scanf("%d",&command);
                system("clear");
                if(command == 1){
                    batting_result = batting(A_batter[A_order][0],A_batter[A_order][1],A_batter[A_order][2],A_batter[A_order][3],B_pitcher[B_P][0],B_pitcher[B_P][1],B_pitcher[B_P][2],B_pitcher[B_P][3]);
                    B_pitcher[B_P][2] = B_pitcher[B_P][2] - GetRandom(1,4);
                }else if(command == 2){
                    batting_result = batting(A_batter[A_order][0],A_batter[A_order][1],A_batter[A_order][2],A_batter[A_order][3],B_pitcher[B_P][0]+5,B_pitcher[B_P][1],B_pitcher[B_P][2]-20,B_pitcher[B_P][3]-10);
                    B_pitcher[B_P][2] = B_pitcher[B_P][2] - GetRandom(1,4);
                }else if(command == 3){
                    batting_result = batting(A_batter[A_order][0],A_batter[A_order][1],A_batter[A_order][2],A_batter[A_order][3],B_pitcher[B_P][0]-5,B_pitcher[B_P][1],B_pitcher[B_P][2]+5,B_pitcher[B_P][3]+10);
                    B_pitcher[B_P][2] = B_pitcher[B_P][2] - GetRandom(1,4);
                }else if(command == 4){
                    batting_result = batting(A_batter[A_order][0],A_batter[A_order][1],A_batter[A_order][2],A_batter[A_order][3],B_pitcher[B_P][0]+5,B_pitcher[B_P][1]+10,B_pitcher[B_P][2]-7,B_pitcher[B_P][3]+10);
                    B_pitcher[B_P][2] = B_pitcher[B_P][2] - GetRandom(1,4);
                }else if(command == 5){
                    system("clear");
                    printf("\n\n\n");
                    printf("********************\n");
                    printf("   ピッチャー交代\n");
                    printf("********************\n\n");
                    printf("現在のピッチャー\n\n");
                    if(B_P == 0){printf("過去永");}
                    else if(B_P == 1){printf("戸卿");}
                    else if(B_P == 2){printf("小勢");}
                    else if(B_P == 3){printf("小谷");}
                    printf("  残体力:%d\n\n\n",B_pitcher[B_P][2]);
                    printf("0,過去永  球速:%d  コントロール:%d  スタミナ:%d  変化球:%d\n\n",B_pitcher[0][0],B_pitcher[0][1],B_pitcher[0][2],B_pitcher[0][3]);
                    printf("1,戸卿    球速:%d  コントロール:%d  スタミナ:%d  変化球:%d\n\n",B_pitcher[1][0],B_pitcher[1][1],B_pitcher[1][2],B_pitcher[1][3]);
                    printf("2,小勢    球速:%d  コントロール:%d  スタミナ:%d  変化球:%d\n\n",B_pitcher[2][0],B_pitcher[2][1],B_pitcher[2][2],B_pitcher[2][3]);
                    printf("3,小谷    球速:%d  コントロール:%d  スタミナ:%d  変化球:%d\n\n",B_pitcher[3][0],B_pitcher[3][1],B_pitcher[3][2],B_pitcher[3][3]);
                    scanf("%d",&B_P);
                    printf("\n\n\n");
                }

                if (B_pitcher[B_P][3] <= 20){
                    B_pitcher[B_P][0] = B_pitcher[B_P][0] - 10;
                    B_pitcher[B_P][1] = B_pitcher[B_P][1] - 30;
                    B_pitcher[B_P][3] = B_pitcher[B_P][3] - 20;
                }
                if(A_order == 0){printf("1番 鈴木\n");}
                else if(A_order == 1){printf("2番 外島\n");}
                else if(A_order == 2){printf("3番 赤木\n");}
                else if(A_order == 3){printf("4番 城鳥\n");}
                else if(A_order == 4){printf("5番 大笠原\n");}
                else if(A_order == 5){printf("6番 内山\n");}
                else if(A_order == 6){printf("7番 柿原\n");}
                else if(A_order == 7){printf("8番 石村\n");}
                else if(A_order == 8){printf("9番 両岡\n");}
                A_order++;
                
                if (A_order == 9){
                    A_order = 0;
                }
                if(B_P == 0){printf("P:過去永");}
                else if(B_P == 1){printf("P:戸卿");}
                else if(B_P == 2){printf("P:小勢");}
                else if(B_P == 3){printf("P:小谷");}
                printf("  残体力:%d\n",B_pitcher[B_P][2]);
                printf("球速:%d コン:%d スタ:%d 変:%d\n\n",B_pitcher[B_P][0],B_pitcher[B_P][1],B_pitcher[B_P][2],B_pitcher[B_P][3]);
                }
//********************************************************************************************
//***************** ウラ **********************************************************************
                else if(times % 2 == 0){
                command =100;
                while(command > 10 ){
                    printf("バッターに指示を出してください。\n");
                    printf("********************\n");
                    printf("1,任せる\n2,長打狙い\n3,ヒット狙い\n4,バント\n5,盗塁\n");
                    printf("********************\n");
                    scanf("%d",&command);
                    if(command == 1){
                        batting_result = batting(B_batter[B_order][0],B_batter[B_order][1],B_batter[B_order][2],B_batter[B_order][3],A_pitcher[0],A_pitcher[1],A_pitcher[2],A_pitcher[3]);
                    system("clear");
                    }
                    else if(command == 2){
                        batting_result = batting(B_batter[B_order][0],B_batter[B_order][1]-15,B_batter[B_order][2]+20,B_batter[B_order][3],A_pitcher[0],A_pitcher[1],A_pitcher[2],A_pitcher[3]);
                    system("clear");
                    }
                    else if(command == 3){
                        batting_result = batting(B_batter[B_order][0],B_batter[B_order][1]+20,B_batter[B_order][2]-10,B_batter[B_order][3],A_pitcher[0],A_pitcher[1],A_pitcher[2],A_pitcher[3]);
                    system("clear");
                    }
                    else if(command == 4){
                        i = bunt(B_batter[B_order][1],A_pitcher[0],A_pitcher[3]);

                        batting_result = batting(0,0,0,0,0,0,0,0);
                        if(i == 1){
                            printf("バントが成功しました!!\n\n");
                            runner = runner * 10;
                            o++;
                            break;
                            command =100;

                        }else{
                            printf("バントに失敗しました。\n");
                            o++;
                        }
                    B_order++;
                    system("clear");

                    }
                    else if (command == 5){
                        if(runner == 1 || runner == 101){
                            i = stolen_base(B_batter[B_P][3],A_batter[3][4]);
                            if(i == 0){
                                printf("盗塁に失敗しました!!アウトカウントが一つ増えます。\n\n");
                                o++;
                                command = 100;
                                }
                            else if(i == 1){
                                if(runner == 1){runner = 10;}
                                else if(runner == 101){runner = 110;}
                                printf("盗塁に成功しました!!\n\n");
                                command = 100;
                            }
                        }else{printf("ランナーがいないか、ランナーが「お前なんかのために命を捨てたくない」と言っています\n"); command = 100;}
                    system("clear");
                    }
                }

                if(B_order == 0){printf("1番 周西\n");}
                else if(B_order == 1){printf("2番 遠藤\n");}
                else if(B_order == 2){printf("3番 小谷\n");}
                else if(B_order == 3){printf("4番 吉畑\n");}
                else if(B_order == 4){printf("5番 村下\n");}
                else if(B_order == 5){printf("6番 本岡\n");}
                else if(B_order == 6){printf("7番 山畑\n");}
                else if(B_order == 7){printf("8番 源畑\n");}
                else if(B_order == 8){printf("9番 中町\n");}
            
                B_order++;
                if(B_order == 9){
                    B_order = 0;
                }
            }
//**********Hit Count*****************************//
            
            if(batting_result >= 1){
                if(times == 1 || times % 2 == 1){
                    A_H = A_H + 1;
                }else{
                    B_H = B_H + 1;
                }
            }
            
            if(batting_result == 0){
                printf("Out\n");
                o++;
            }else if(batting_result == 1){
                printf("hit\n");
                runner = runner * 10 + 1;
            }else if(batting_result == 2){
                printf("two base hit\n");
                runner = runner * 100 + 10;
            }else if(batting_result == 3){
                printf("three base hit\n");
                runner = runner * 1000 + 100;
            }else if(batting_result == 4){
                printf("Home Run\n");
                runner = runner * 10000 + 1000;
            }


            if (runner >= 1000){
                int HomeIn = runner / 1000;

                if(HomeIn == 1111){
                    if (times % 2 == 1){
                        A[t] =A[t] + 4; 
                    }else{
                        B[t] =B[t] + 4;
                    }
                }else if(HomeIn == 111 || HomeIn == 1101 || HomeIn == 1011|| HomeIn == 111){
                    if (times % 2 == 1){
                        A[t] =A[t] + 3; 
                    }else{
                        B[t] =B[t] + 3;
                    }
                }else if(HomeIn == 101 ||HomeIn == 11 || HomeIn == 1001){
                    if (times % 2 == 1){
                        A[t] =A[t] + 2; 
                    }else{
                        B[t] =B[t] + 2;
                    }
                }else if(HomeIn == 100 ||HomeIn == 10 ||HomeIn == 1 || HomeIn == 1000){
                    if (times % 2 == 1){
                        A[t] =A[t] + 1; 
                    }else{
                        B[t] =B[t] + 1;
                    }
                }
                
                runner = runner % 1000;
            }

            printf("------------------------------\n");
            if(runner == 10 || runner == 11 || runner == 110 || runner == 111){
                printf("            [#]  \n\n\n\n\n");
            }else{
                printf("            [ ]  \n\n\n\n\n");
            }
            
            if(runner == 100 || runner == 110 || runner == 101 || runner == 111){
                printf("[#]");
            }else{
                printf("[ ]");
            }

            if(runner == 1 || runner == 11 || runner == 111 || runner == 101){
                printf("                      [#]\n\n\n\n\n");
            }else if(runner == 0){
                printf("                      [ ]\n\n\n\n\n");
            }else{
                printf("                      [ ]\n\n\n\n\n");
            }

            printf("            < > %dアウト  \n",o);
            printf("------------------------------\n\n");


            if (o ==3){
                times++;
                runner = 0;
                printf("\n");
            }

        }
//******チーム総得点*******************
        if(times % 2 == 1){
            A_R = A_R + A[t];
        }
        B_R = B_R + B[t];

//***************************************************************** 
//******Score board************************************************ 

        printf("   1  2  3  4  5  6  7  8  9   R  H  E\n");
        printf(" +---------------------------+--------+\n");
        printf("A|");
        for(i = 0; i< 9; i++){
            printf(" %d ",A[i]);
        }
        printf("| %d  %d  0|\n",A_R,A_H);
        printf("B|");
        for(i =0 ; i< 9;i++){
            printf(" %d ",B[i]);
        }
        printf("| %d  %d  0|\n",B_R,B_H);
        printf(" +---------------------------+--------+\n\n");
//******************************************************************
//****************************************************************** 
    
    }

    if(A_R == B_R){
        printf("*********************\n");
        printf("*        DRAW       *\n");
        printf("*********************\n");
    }else if(A_R >B_R){
        printf("*********************\n");
        printf("*   YOU ARE LOSER   *\n");
        printf("*********************\n");
    }else if(A_R < B_R){
        printf("**********************\n");
        printf("*   YOU ARE WINNER   *\n");
        printf("**********************\n");
    }
    return 0;
}
