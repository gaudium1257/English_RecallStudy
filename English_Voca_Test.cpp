#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <conio.h> // 키 입력 인식 기능

#include <windows.h> // 색상 변경 기능

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char * argv[]) {

    char start_key, quit_key;
    char line_spell[1000], line_mean[3][1000];
    int i = 0, j = 0;
    srand(time(NULL));

    // 기본적인 프로그램 사용 설명 
    printf("\n---영단어 외우기---");
    printf("\n\n\n<설명>");
    printf("\n\n- 이 프로그램은 효과적인 영단어 학습을 위한 프로그램입니다");
    printf("\n- 영단어가 제시되고 각기 다른 세 가지의 뜻이 나타날 것입니다");
    printf("\n- 셋 중 하나의 뜻만 정답이고 나머지 뜻은 오답입니다");
    printf("\n- 1, 2, 3 중 하나의 키를 눌러 정답에 답하시면 됩니다");
    printf("\n\nex)");
    printf("\ncombination");
    printf("\n1. 조합[결합](물), 조합[연합] (행위)");
    printf("\n2. 결국 (어떤 처지에) 처하게 되다");
    printf("\n3. 기쁨, 즐거움");
    printf("\n\n이 예시에서는 1번 키를 누르면 정답으로 처리 됩니다");
    printf("\n\n- 단어의 출처는 네이버 영어사전의 고1_교과서 단어장 입니다");
    printf("\n- 이제 Enter키를 눌러 테스트를 시작하십시오");

    while (1) { // Enter 키를 누를 시 프로그램을 시작하는 코드
        start_key = _getch();

        if (start_key == '\r' || start_key == '\n') {
            printf("\n\n프로그램을 시작합니다");
            break;
        }
    }

    // 몇 개의 영단어 시험을 볼 건지 입력받는 코드
    int test_voca_num;
    input:
        printf("\n\n테스트할 영단어 개수를 입력하십시오 (1~200) : ");
    scanf("%d", & test_voca_num);
    if (test_voca_num >= 1 && test_voca_num <= 200) {
        printf("\n테스트를 시작하겠습니다");
    } else {
        printf("\n입력한 숫자가 적절하지 않습니다");
        goto input;
    }
	
    int testing_voca_num[200] = {};
    int correct_num = 0;
    int wrong_num = 0;
    int voca_random = 0;
    FILE * file_spell;
    file_spell = fopen("word_spellingg.txt", "r");


    FILE * file_mean;
    file_mean = fopen("word_meaningg.txt", "r");

    if (file_spell == NULL || file_mean == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;

    }


    for (i = 0; i < test_voca_num; i++) {
        random:
            voca_random = (rand() % 200) + 1;
        for (j = 0; j < i; j++) {
            if (testing_voca_num[j] == voca_random) {
                goto random;
            }
        }
        testing_voca_num[i] = voca_random;

        rewind(file_spell);
        rewind(file_mean);

        int currentLine_spell = 0;
        int currentLine_mean = 0;

        while (fgets(line_spell, sizeof(line_spell), file_spell) != NULL) {
            currentLine_spell++;
            if (currentLine_spell == voca_random) {
                // 뜻 선택 및 섞기
                for (int k = 0; k < 3; k++) {
                    int randLine = (rand() % 200) + 1;
                    while (randLine == voca_random) {
                        randLine = (rand() % 200) + 1;
                    }
                    rewind(file_mean);
                    currentLine_mean = 0;
                    while (fgets(line_mean[k], sizeof(line_mean[k]), file_mean) != NULL) {
                        currentLine_mean++;
                        if (currentLine_mean == randLine) {
                            // 줄 끝의 개행 문자 제거
                            line_mean[k][strcspn(line_mean[k], "\n")] = '\0';
                            break;
                        }
                    }
                }

                // 뜻 위치 랜덤으로 변경
                for (int k = 2; k > 0; k--) {
                    int r = rand() % (k + 1);
                    char temp[1000];
                    strcpy(temp, line_mean[k]);
                    strcpy(line_mean[k], line_mean[r]);
                    strcpy(line_mean[r], temp);
                }
				
				char line_imsi[5][1000]={};
				rewind(file_mean);
				currentLine_mean = 0;
				while (fgets(line_imsi[0], sizeof(line_imsi[0]), file_mean) != NULL) {
                    currentLine_mean++;
                    if (currentLine_mean == voca_random) {
                        // 줄 끝의 개행 문자 제거
                        line_imsi[0][strcspn(line_imsi[0], "\n")] = '\0';
                        break;
                    }
                }
				
				int random_plus = ((rand() + 1257) * rand()) % 3;
				strcpy(line_mean[random_plus], line_imsi[0]);
				
                // 출력
                printf("\nNO.%d : %s", i+1, line_spell);
                for (int k = 0; k < 3; k++) {
                    printf("\n%d. %s", k + 1, line_mean[k]);
                }


                // 사용자 입력 및 정답 체크
                int correct_option = random_plus + 1; // 옳은 뜻 랜덤 
                int user_choice;
                printf("\n\n답을 입력하세요! (1, 2, 3): ");
                scanf("%d", &user_choice);

                if (user_choice == correct_option) {
                    printf("정답입니다!\n\n");
                    correct_num++;
                } else {
                    printf("오답입니다! 정답은 %d. %s입니다.\n\n", correct_option, line_mean[correct_option - 1]);
                    wrong_num++;
                }

                
                break;
            }
        }
    }

	fclose(file_spell);
	fclose(file_mean);
	
    printf("\n\n정답의 개수 : %d \n오답의 개수 : %d \n정답률 : %.1f%%", correct_num, wrong_num, (double)correct_num/(correct_num + wrong_num)*100);

    printf("\n\n\n- 이제 Enter키를 눌러 프로그램을 종료하십시오");
    while (1) { // Enter 키를 누를 시 프로그램을 종료하는 코드 
        quit_key = _getch();

        if (quit_key == '\r' || quit_key == '\n') {
            printf("\n\n프로그램을 종료합니다");
            break;
        }
    }

    return 0;
}

