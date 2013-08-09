/*****************************************************************************
Author: subjectZero                                                          *
Course: CIS111 - C Programming Language                                      *
Assignment: Programming Project #01 - Grade Calculator                       *
Date created: 23 September 2012                                              *
Last modified: 9 August 2013                                                 *
                                                                             *
Description: This program allows the user to enter each of the grades earned *
				on each of his or her (projects 1-3,  the midterm exam,  and *
 				the user's attendance score). The program then processes the *
				data,  and finally outputs  the minimum score the  user must *
				earn on  the final exam  to earn an  A, B, C, or D grade for *
				the course.                                                  *
*****************************************************************************/

//      PROGRAM INCLUDES
#include <stdio.h>

//      PROTOTYPES
void clearBuf(void);

int main() {
	//  POINTS EARNED
	int project1 = 0 ;
	int project2 = 0 ;
	int project3 = 0 ;
	int midExam = 0 ;
	int attendance = 0 ;
	double totalPoints = 0 ;

	//  MINIMUM GRADE REQUIREMENTS IN POINTS
	double MIN_PNTS_A = 900.0 ;
	double MIN_PNTS_B = 800.0 ;
	double MIN_PNTS_C = 700.0 ;
	double MIN_PNTS_D = 600.0 ;

	//  SCORE ON FINAL TO EARN EACH GRADE
	double pnts4A = 0.0 ;
	double pnts4B = 0.0 ;
	double pnts4C = 0.0 ;
	double pnts4D = 0.0 ;

	double percent4A = 0.0 ;
	double percent4B = 0.0 ;
	double percent4C = 0.0 ;
	double percent4D = 0.0 ;
	
	//------------------------INPUT-------------------------------------//
	//  USER PROMPTED TO INPUT GRADES

	//  Priming read
	printf("Please enter the grade for project #1 (0-200)  : ");
	scanf("%d", &project1);
	
	
	//  Sanity loop
	while(project1 < 0 || project1 > 200) {
		printf("I'm sorry, you entered an invalid grade.\n");
		printf("Please enter the grade for project #1 (0-200)  : ");
		scanf("%d", &project1);
		clearBuf();
	}

	//  Priming read
	printf("Please enter the grade for project #2 (0-200)  : ");
	scanf("%d", &project2);
	clearBuf();

	//  Sanity loop
	while(project2 < 0 || project2 > 200) {
		printf("I'm sorry, you entered an invalid grade.\n");
		printf("Please enter the grade for project #2 (0-200)  : ");
		scanf("%d", &project2);
		clearBuf();
	}
	//  Priming read
	printf("Please enter the grade for project #3 (0-200)  : ");
	scanf("%d", &project3);
	clearBuf();

	// Sanity loop
	while(project3 < 0 || project3 > 200) {
		printf("I'm sorry, you entered an invalid grade.\n");
		printf("Please enter the grade for project #3 (0-200): ");
		scanf("%d", &project3);
		clearBuf();
	}
	//  Priming read
	printf("Please enter the grade for midterm exam (0-150): ");
	scanf("%d", &midExam);
	clearBuf();

	//  Sanity loop
	while(midExam < 0 || midExam > 150) {
		printf("I'm sorry, you entered an invalid grade.\n");
		printf("Please enter the grade for midterm exam (0-150): ");
		scanf("%d", &midExam);
		clearBuf();
	}
	//  Priming read
	printf("Please enter your attendance score (0-100)     : ");
	scanf("%d", &attendance);
	clearBuf();

	//  Sanity loop
	while(attendance < 0 || attendance > 100) {
		printf("I'm sorry, you entered an invalid grade.\n");
		printf("Please enter your attendance score (0-100): ");
		scanf("%d", &attendance);
		clearBuf();
	}

	//------------------------PROCESSING--------------------------------//
	totalPoints =  project1 + project2 + project3 + midExam + attendance;
	pnts4A = (MIN_PNTS_A - totalPoints);     
	pnts4B = (MIN_PNTS_B - totalPoints); 
	pnts4C = (MIN_PNTS_C - totalPoints); 
	pnts4D = (MIN_PNTS_D - totalPoints); 

	percent4A = ( ( pnts4A * 2 ) / 3 );
	percent4B = ( ( pnts4B * 2 ) / 3 ); 
	percent4C = ( ( pnts4C * 2 ) / 3 ); 
	percent4D = ( ( pnts4D * 2 ) / 3 );
	//------------------------OUTPUT------------------------------------//
	//  User input is echoed in form of Grade Summary
	printf("\n");
	printf("GRADE SUMMARY\n");
	printf("-------------\n");
	printf("Project #1  : %d\n", project1);
	printf("Project #2  : %d\n", project2);
	printf("Project #3  : %d\n", project3);
	printf("Midterm Exam: %d\n", midExam);
	printf("Attendance  : %d\n\n", attendance);

	//  Points/percent needed on final to earn grade displayed as table
	printf("COURSE GRADE    | POINTS NEEDED ON FINAL");
	printf("          | PERCENTAGE NEEDED ON FINAL\n");
	printf("A               | %-32.0f| %.2f%%\n", pnts4A, percent4A);
	printf("B               | %-32.0f| %.2f%%\n", pnts4B, percent4B);
	printf("C               | %-32.0f| %.2f%%\n", pnts4C, percent4C);
	printf("D               | %-32.0f| %.2f%%\n", pnts4D, percent4D);
	printf("\n");
	printf("Any score below %.2f%% on the final exam will ", percent4D);
	printf("result in a \n");
	printf("failing grade for the semester.\n\n");
	//------------------------EXIT--------------------------------------//
	printf("Press any key to continue...\n");
	getchar();

	return 0;
}

void clearBuf(void) {
	while(getchar() != '\n');
}

