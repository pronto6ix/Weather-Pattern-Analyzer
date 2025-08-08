#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max_Line_Len 1000
#define START_YR 1760
#define END_YR 2015
#define MAX_MONTHS 12
#define START_YEAR 1801
#define END_YEAR 2000
#define MAX_YEARS (END_YEAR - START_YEAR + 1)
#define MAX_MONTHS 12
#define START_YR_Q8 1850
#define END_YEAR_19TH 1899
#define START_YEAR_20TH 1900
#define END_YEAR_20TH 1999
#define START_YEAR_21ST 2000
#define END_YEAR_21ST 2015


// Array for the names of the months
char *month_names[MAX_MONTHS] = {
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
};


//Function used to convert the dates in the first column into years
int convert_date_to_year_1st_column(char *date){
  int year;
  sscanf(date, "%d-", &year); //only extracts an integer value followed by a hyphen
  return year;
}

//User-defined function associated with question 1
void question1(FILE *file){
  //initializing variables
  char line[Max_Line_Len];

  //The following variables are used in order to keep track of the year being processed
  int current_yr=START_YR;
  int count=0;
  double sum=0.0;
  double hottest_temp = -1000.0; // Initializing with a very low temperature
  double coldest_temp = 1000.0;  // Initializing with a very high temperature
  int hottest_year = START_YR;
  int coldest_year = START_YR;


  //opening file to write data on
  FILE*in= fopen("question6.txt", "w");
  //heading for the data 
  fprintf(in, "# year average\n");

  /*While loop used to go through each line
   * from the file until the last year is reached using 'fgets'*/

  while(fgets(line,sizeof(line), file) != NULL)
  {
    /*Since columns are seperated by commas, the comma is used as a
     * delimiter. First token is then exptracted from the data 
     * using 'strcpy' and copied to the 'date' variable*/
    char *token=strtok(line, ",");
    char date[20];
    strcpy(date, token);

    //Following line is called in order to year date from the string holding the date
    int year=convert_date_to_year_1st_column(date);

    /*Condition used to check if extracted year is within the range*/
    if(year>=START_YR && year<=END_YR)
    {
    /*If the year is within range, 'strtok' gets called to obtain the 
     * token that represents the temperature */
      token=strtok(NULL, ",");
    /*Token gets converted to a long-float number using 'atof' and is then
     * stored into the 'temp' (temperature) variable*/
      double temp=atof(token);

    /*If the year aligns with the year currently being processed, the
     * temperature gets added to the sum and then the count is incremented.
     * Then, if the year changes, the previous years' average temperature
     * is calculated and printed.*/
      if(year==current_yr)
      {
        sum+=temp;
        count++;
      }

      else
      {
        if (count>0)
        {
          double aver=sum/count;

          printf("Average temperature for %d is %.3lf\n", current_yr, aver);
          //printing year and average on .txt file for Question 6
          fprintf(in, "%d %.3lf\n", current_yr, aver);

          //finding which is the hottest or coldest year
          if (sum / count > hottest_temp) {
            hottest_temp = sum / count;
            hottest_year = current_yr;
          }
          if (sum / count < coldest_temp) {
            coldest_temp = sum / count;
            coldest_year = current_yr;
          }
        }
        /*sum and count get reset here for the new year*/
        sum=temp;
        count=1;
        current_yr=year;
      }
    }
  }

  /*Once the loop ends, any remaining temperature readings have their average
   * calculated and printed*/

  if (count>0)
  {
    double aver=sum/count;
    printf("Average temperature for %d is %.3lf\n", current_yr, aver);
    fprintf(in, "%d %.3lf\n", current_yr, aver);
    if (sum / count > hottest_temp) {
      hottest_temp = sum / count;
      hottest_year = current_yr;
    }
    if (sum / count < coldest_temp) {
      coldest_temp = sum / count;
      coldest_year = current_yr;
    }
  }

  //Question 5 code output
  printf("\nThe hottest year is %d\n", hottest_year);
  printf("The coldest year is %d\n", coldest_year);

  fclose(in);


}

//Function declaration for the function that solves the second question
void question2(FILE *file){
  /*Variables used to store the sum and count of the temperatures
   * of each century*/

  double sum18=0.0,sum19=0.0,sum20=0.0,sum21=0.0;
  int count18=0,count19=0,count20=0,count21=0;

  char line[Max_Line_Len];//array used to store lines read from file
  /*while loop used to read each line from the file until the last line*/
  while(fgets(line,Max_Line_Len,file) != NULL)
  {
    char *date=strtok(line, ",");
    double temp=atof(strtok(NULL, ","));

    /*tokenizing based on hyphen delimiter becuase of the format of 
     * the date within the file only extracting the year from the date with the
     * following format "year-month-day"*/
    int year=atoi(strtok(date,"-"));


  /*multiple if-else statements that sorts and categorizes temperatures into
   * their century based on the year that was extracted. The sum and count
   * are updated for each centuries temperatures*/
    if(year>=1760 && year<=1799)
    {
      sum18+=temp;
      count18++;
    }
    else if (year>=1800 && year<=1899)
    {
      sum19+=temp;
      count19++;
    }
    else if (year>=1900 && year<=1999)
    {
      sum20+=temp;
      count20++;
    }
    else if (year>=2000 && year<=2015)
    {
      sum21+=temp;
      count21++;
    }
  }

  /*average is calculated and displayed using the following*/

  printf("18th century temperature average is %.3lf\n", sum18/count18);
  printf("19th century temperature average is %.3lf\n", sum19/count19);
  printf("20th century temperature average is %.3lf\n", sum20/count20);
  printf("21st century temperature average is %.3lf\n", sum21/count21);
}

// Function to parse each line of the CSV file
void question3(char *line, double monthly_totals[], int monthly_counts[]) {
    char *date_str = strtok(line, ",");
    char *temperature_str = strtok(NULL, ",");

    // Check if both date and temperature are parsed successfully
    if (date_str == NULL || temperature_str == NULL) {
        printf("Skipping invalid line.\n");
        return;
    }

    // Extract year and month from the date
    int year, month;
    sscanf(date_str, "%d-%d", &year, &month);
    month--;

    // Check if the year falls within the range 1900 to 2015
    if (year >= 1900 && year <= 2015) {
        // Convert temperature from string to double
        double temperature = atof(temperature_str);
        // Update monthly total temperature and count
        monthly_totals[month] += temperature;
        monthly_counts[month]++;
    }
}

// Function to print monthly averages
void printquestion3(double monthly_totals[], int monthly_counts[]) {
    printf("Monthly Averages between 1900 - 2015:\n");
    for (int i = 0; i < MAX_MONTHS; i++) {
        double average = (monthly_counts[i] > 0) ? monthly_totals[i] / monthly_counts[i] : 0;
        printf("%s: %.2f\n", month_names[i], average);
    }
}


// Function to parse each line of the CSV file
void question4(char *line, double monthly_totals[], int monthly_counts[], double *hottest_temp, double *coldest_temp, int *hottest_month, int *coldest_month, int *hottest_year, int *coldest_year) {
    char *date_str = strtok(line, ",");
    char *temperature_str = strtok(NULL, ",");

    // // Check if both date and temperature are parsed successfully
    if (date_str == NULL || temperature_str == NULL) {
        return;
    }

    // Extract year and month from the date
    int year, month;
    sscanf(date_str, "%d-%d", &year, &month);
    month--;

    // Check if the year falls within the range 1760 to 2015
    if (year >= 1760 && year <= 2015) {
        // Convert temperature from string to double
        double temperature = atof(temperature_str);
        // Update monthly total temperature and count
        monthly_totals[month] += temperature;
        monthly_counts[month]++;

        // Check for hottest temperature
        if (temperature > *hottest_temp) {
            *hottest_temp = temperature;
            *hottest_month = month;
            *hottest_year = year;
        }

        // Check for coldest temperature
        if (temperature < *coldest_temp) {
            *coldest_temp = temperature;
            *coldest_month = month;
            *coldest_year = year;
        }
    }
}

// Function to display results
void printquestion4(double hottest_temp, int hottest_month, int hottest_year, double coldest_temp, int coldest_month, int coldest_year) {
    // Display the hottest month
    printf("Hottest month recorded:\n");
    printf("Month: %s, Year: %d, Temperature: %.2f degrees celsius \n", month_names[hottest_month], hottest_year, hottest_temp);

    // Display the coldest month
    printf("Coldest month recorded:\n");
    printf("Month: %s, Year: %d, Temperature: %.2f degrees celsius \n", month_names[coldest_month], coldest_year, coldest_temp);
}


void question7(FILE *file){
    // Initializing variables
    char line[Max_Line_Len];
    // Open a file to write the average temperatures
    FILE *outputFile = fopen("question7.txt", "w");
    if (outputFile == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
    // Initialize arrays to store sums and counts for each century
    double sum_19th_century[MAX_YEARS] = {0.0};
    int count_19th_century[MAX_YEARS] = {0};
    double sum_20th_century[MAX_YEARS] = {0.0};
    int count_20th_century[MAX_YEARS] = {0};
    /* While loop used to go through each line
     * from the file until the last year is reached using 'fgets'*/
    while (fgets(line, sizeof(line), file) != NULL) {
        /* Since columns are separated by commas, the comma is used as a
         * delimiter. First token is then extracted from the data
         * using 'strcpy' and copied to the 'date' variable */
        char *token = strtok(line, ",");
        char date[20];
        strcpy(date, token);
        // Following line is called in order to extract the year date from the string holding the date
        int year = convert_date_to_year_1st_column(date);
        /* If the year is within the 19th century (1801-1900) */
        if (year >= 1801 && year <= 1900) {
            /* 'strtok' gets called to obtain the
             * token that represents the temperature */
            token = strtok(NULL, ",");
            /* Token gets converted to a double number using 'atof' and is then
             * stored into the 'temp' (temperature) variable */
            double temp = atof(token);
            /* Add the temperature to the sum of the corresponding year and increment count */
            sum_19th_century[year - START_YEAR] += temp;
            count_19th_century[year - START_YEAR]++;
        }
        /* If the year is within the 20th century (1901-2000) */
        else if (year >= 1901 && year <= 2000) {
            /* 'strtok' gets called to obtain the
             * token that represents the temperature */
            token = strtok(NULL, ",");
            /* Token gets converted to a double number using 'atof' and is then
             * stored into the 'temp' (temperature) variable */
            double temp = atof(token);
            /* Add the temperature to the sum of the corresponding year and increment count */
            sum_20th_century[year - START_YEAR] += temp;
            count_20th_century[year - START_YEAR]++;
        }
    }
    /* Print the average temperatures for each year from 1801 to 2000 */
    /* Print the average temperatures for each year from 1801 to 2000 */
   /* Print the average temperatures for each year from 1801 to 2000 */
   /* Print the average temperatures for each year from 1 to 100 */
   fprintf(outputFile, "Year\tAverage Temperature 19th Century\tAverage Temperature 20th Century\n");
   for (int i = 0; i < 100; i++) {
       // Calculate the year
       int year = i + 1;
       // Print the year (treated as 1-100)
       fprintf(outputFile, "%d\t", year);
       // Print the average temperature for the 19th century (1801) and the 20th century (1901)
       int idx_1801 = (1801 - START_YEAR) + i;
       int idx_1901 = (1901 - START_YEAR) + i;
       double aver_19th = count_19th_century[idx_1801] > 0 ? sum_19th_century[idx_1801] / count_19th_century[idx_1801] : 0;
       double aver_20th = count_20th_century[idx_1901] > 0 ? sum_20th_century[idx_1901] / count_20th_century[idx_1901] : 0;
       fprintf(outputFile, "%.3lf\t%.3lf\n", aver_19th, aver_20th);
   }
   fclose(outputFile);
}

  /*Function for question 8 to read the land average, land max, and land min
   * temperatures from the csv file and input the yearly averaged data into a 
   * .txt file. Within the function declaration, an argument for a pointer to 'FILE'
   * objects representing the csv file being read and the argument for a pointer
   * to the output txt file is made */
void question8(FILE *input_file, FILE *output_file){
    /*line used to read and discard the header line from the input file
     * using 'fgets' function*/
    char header[Max_Line_Len];
    fgets(header,sizeof(header),input_file);

    fprintf(output_file, "#Year LandAverageTemperature LandMaxTemperature LandMinTemperature\n");

    /*Initializing variables*/
    int current_yr=START_YR_Q8;
    double sum_land_avg_temp=0.0;
    double sum_land_max_temp=0.0;
    double sum_land_min_temp=0.0;
    int count=0;

    /*while loop used to loop file untile the end of 2015 is reached*/
    char line[Max_Line_Len];
    while(fgets(line,sizeof(line), input_file) != NULL)
    {
      /*Lines used to parse the year from the current line. Commas are used as
       * delimiters as 'strtok' is used to tokenize the line. 'strncpy' is used
       * in order to extract the year substring. 'atoi' is used to convert
       * the substring into an integer number.*/
      char *token=strtok(line, ",");
      char year_str[5];
      strncpy(year_str, token, 4);
      year_str[4]='\0';
      int year=atoi(year_str);

      /*if statement condition used to check if the year is between 1850 and 2015*/
      if(year>=START_YR_Q8 && year<=END_YR)
      {
        token=strtok(NULL, ",");//Skip first column

        //Accumulate the (LandAverageTemperature) column
        double land_avg_temp=atof(token);
        sum_land_avg_temp+=land_avg_temp;

        token=strtok(NULL, ",");//Skip third column

        /*These lines accumulate the column for the LandMaxTemperature*/
        token=strtok(NULL, ",");
        double land_max_temp=atof(token);
        sum_land_max_temp+=land_max_temp;

        token=strtok(NULL, ",");//Skip fifth column

        /*These lines accumulate the column for the LandMinTemperature*/
        token=strtok(NULL, ",");
        double land_min_temp=atof(token);
        sum_land_min_temp += land_min_temp;

        count++; //Increments count of months being processed per current year

        /*Condition used to check if all months in the current year have been processed*/
        if(count == MAX_MONTHS)
        {
          /*Calculating temperature of land, land max and land min temperatures*/
          double avg_LAT=sum_land_avg_temp/MAX_MONTHS;
          double avg_LMAXT=sum_land_max_temp/MAX_MONTHS;
          double avg_LMINT=sum_land_min_temp/MAX_MONTHS;

          fprintf(output_file, "%d %.3lf %.3lf %.3lf\n", current_yr, avg_LAT, avg_LMAXT, avg_LMINT);

          /*Lines used to reset the accumulation variables and proceed to next year*/
          sum_land_avg_temp=0.0;
          sum_land_max_temp=0.0;
          sum_land_min_temp=0.0;
          count=0;
          current_yr++;
        }
      }
    }
  }


void question9(FILE *input_file) {
    char header[Max_Line_Len];
    fgets(header, sizeof(header), input_file);

    FILE *output_file = fopen("question9.txt", "w");

    fprintf(output_file, "#Century LandAverageTemperature LandMinTemperature LandMaxTemperature\n");

    double sum_land_avg_temp_19 = 0.0;
    double sum_land_max_temp_19 = 0.0;
    double sum_land_min_temp_19 = 0.0;
    int count_19 = 0;

    double sum_land_avg_temp_20 = 0.0;
    double sum_land_max_temp_20 = 0.0;
    double sum_land_min_temp_20 = 0.0;
    int count_20 = 0;

    double sum_land_avg_temp_21 = 0.0;
    double sum_land_max_temp_21 = 0.0;
    double sum_land_min_temp_21 = 0.0;
    int count_21 = 0;

    char line[Max_Line_Len];
    while (fgets(line, sizeof(line), input_file) != NULL) {
        char *token = strtok(line, ",");
        char year_str[5];
        strncpy(year_str, token, 4);
        year_str[4] = '\0';
        int year = atoi(year_str);

        int century;
        if (year >= START_YR_Q8 && year <= END_YEAR_19TH) {
            century = 19;
        } else if (year >= START_YEAR_20TH && year <= END_YEAR_20TH) {
            century = 20;
        } else if (year >= START_YEAR_21ST && year <= END_YEAR_21ST) {
            century = 21;
        } else {
            continue;
        }

        // Calculate the year within each century
        int year_within_century = year - (century - 1) * 100;

        token = strtok(NULL, ",");
        double land_avg_temp = atof(token);

        token = strtok(NULL, ",");
        double land_max_temp = atof(token);

        token = strtok(NULL, ",");
        double land_min_temp = atof(token);

        // Add temperatures to the corresponding century's sums
        switch (century) {
            case 19:
                sum_land_avg_temp_19 += land_avg_temp;
                sum_land_max_temp_19 += land_max_temp;
                sum_land_min_temp_19 += land_min_temp;
                count_19++;
                break;
            case 20:
                sum_land_avg_temp_20 += land_avg_temp;
                sum_land_max_temp_20 += land_max_temp;
                sum_land_min_temp_20 += land_min_temp;
                count_20++;
                break;
            case 21:
                sum_land_avg_temp_21 += land_avg_temp;
                sum_land_max_temp_21 += land_max_temp;
                sum_land_min_temp_21 += land_min_temp;
                count_21++;
                break;
        }
    }

    // Calculate averages for each century
    double avg_LAT_19 = sum_land_avg_temp_19 / count_19;
    double avg_LMAXT_19 = sum_land_max_temp_19 / count_19;
    double avg_LMINT_19 = sum_land_min_temp_19 / count_19;

    double avg_LAT_20 = sum_land_avg_temp_20 / count_20;
    double avg_LMAXT_20 = sum_land_max_temp_20 / count_20;
    double avg_LMINT_20 = sum_land_min_temp_20 / count_20;

    double avg_LAT_21 = sum_land_avg_temp_21 / count_21;
    double avg_LMAXT_21 = sum_land_max_temp_21 / count_21;
    double avg_LMINT_21 = sum_land_min_temp_21 / count_21;

    // Write averages to the output file with the century column
    fprintf(output_file, "19 %.3lf %.3lf %.3lf\n", avg_LAT_19, avg_LMAXT_19, avg_LMINT_19);
    fprintf(output_file, "20 %.3lf %.3lf %.3lf\n", avg_LAT_20, avg_LMAXT_20, avg_LMINT_20);
    fprintf(output_file, "21 %.3lf %.3lf %.3lf\n", avg_LAT_21, avg_LMAXT_21, avg_LMINT_21);

    fclose(output_file);
}



void question10(FILE *in, char *line, double monthly_totals[], int monthly_counts[],     double monthly_uncertainty[]) {
  char *date_str = strtok(line, ",");
  char *temperature_str = strtok(NULL, ",");
  char *uncertainty_str = strtok(NULL, ",");
  
  // Check if both date, temperature, and uncertainty are parsed successfully
  if (date_str == NULL || temperature_str == NULL || uncertainty_str == NULL) {
      return;
  }

// Extract year and month from the date
  double year, month;
  sscanf(date_str, "%lf-%lf", &year, &month);
  month--;
  
  // Check if the year falls within the range 2000 to 2015
  if (year >= 2000 && year <= 2015) {
      // Convert temperature and uncertainty from string to double
      double temperature = atof(temperature_str);
      double uncertainty = atof(uncertainty_str);
  
      // Update monthly total temperature, count, and uncertainty
      monthly_totals[(int)month] += temperature;
      monthly_counts[(int)month]++;
      monthly_uncertainty[(int)month] += uncertainty; 
  }
}


void question11(FILE *file){
    // Initializing variables
    char line[Max_Line_Len];

    // The following variables are used in order to keep track of the year being processed
    int current_yr = START_YR;
    int count = 0;
    double sum = 0.0;
    double land_ocean_sum = 0.0; // New variable to store sum of Land & Ocean temperatures
    int land_ocean_count = 0; // New variable to count Land & Ocean temperature readings

    // Opening file to write data on
    FILE *in = fopen("question11.txt", "w");
    // Heading for the data
    fprintf(in, "# year avgLandTemp avgLand&OceanTemp\n");

    // While loop used to go through each line from the file until the last year is reached using 'fgets'
    while(fgets(line, sizeof(line), file) != NULL) {
        // Since columns are separated by commas, the comma is used as a delimiter. First token is then extracted from the data
        char *token = strtok(line, ",");
        char date[20];
        strcpy(date, token);

        // Following line is called in order to year date from the string holding the date
        int year = convert_date_to_year_1st_column(date);

        // Condition used to check if extracted year is within the range
        if (year >= START_YR_Q8 && year <= END_YR) {
            // If the year is within range, 'strtok' gets called to obtain the token that represents the temperature
            token = strtok(NULL, ",");
            // Token gets converted to a long-float number using 'atof' and is then stored into the 'temp' (temperature) variable
            double temp = atof(token);


            // Skip the tokens till we reach the LandAndOceanAverageTemperature
            for (int i = 0; i < 6; i++) {
                token = strtok(NULL, ",");
            }

            // Extracting Land & Ocean Average Temperature
            double land_ocean_temp = atof(token);

            // If the year aligns with the year currently being processed, the temperature gets added to the sum and then the count is incremented.
            // Then, if the year changes, the previous years' average temperature is calculated and printed.
            if (year == current_yr) {
                sum += temp;
                land_ocean_sum += land_ocean_temp; // Add Land & Ocean temperature to sum
                count++;
                land_ocean_count++; // Increment count for Land & Ocean temperature
            } else {
                if (count > 0) {
                    double aver = sum / count;
                    double land_ocean_aver = land_ocean_sum / land_ocean_count; // Calculate average Land & Ocean temperature
                    fprintf(in, "%d %.3lf %.3lf\n", current_yr, aver, land_ocean_aver); // Print both averages to file
                }
                // Reset sum and count for the new year
                sum = temp;
                land_ocean_sum = land_ocean_temp; // Reset Land & Ocean sum
                count = 1;
                land_ocean_count = 1; // Reset Land & Ocean count
                current_yr = year;
            }
        }
    }

    // Once the loop ends, any remaining temperature readings have their average calculated and printed
    if (count > 0) {
        double aver = sum / count;
        double land_ocean_aver = land_ocean_sum / land_ocean_count; // Calculate average Land & Ocean temperature
        fprintf(in, "%d %.3lf %.3lf\n", current_yr, aver, land_ocean_aver); // Print both averages to file
    }

    fclose(in);
}



int main(void){
    FILE *file = fopen("GlobalTemperatures.csv", "r");

    // Arrays to store monthly local temperatures     and count
    double monthly_totals[MAX_MONTHS] = {0};
    int monthly_counts[MAX_MONTHS] = {0};
    double monthly_uncertainty[MAX_MONTHS] = {0};

    // Variables to store hottest and coldest temperatures, months, and years
    double hottest_temp = -1000.0; // Set initial value to very low
    double coldest_temp = 1000.0;  // Set initial value to very high
    int hottest_month, coldest_month;
    int hottest_year, coldest_year;

    // Storing each line of the CSV file into a string
    char line[1024];

    // Skipping header line
    fgets(line, sizeof(line), file);

    // Read each line of the file using a while loop
    while (fgets(line, sizeof(line), file)) {
        question3(line, monthly_totals, monthly_counts);
    while (fgets(line,sizeof(line),file)) {
        question4(line, monthly_totals, monthly_counts, &hottest_temp, &coldest_temp, &hottest_month, &coldest_month, &hottest_year, &coldest_year);
        }
    }

    // Resets file pointer to beginning of the file
    fseek(file, 0, SEEK_SET);

   //Display average temperatures for each year
    question1(file);
    printf("\n");

    rewind(file);

    //Display average temperatures for each century 
    question2(file);
    printf("\n");


    rewind(file);

    question7(file);
    printf("\n");

    FILE *input_file = fopen("GlobalTemperatures.csv", "r");
    FILE *output_file = fopen("question8.txt", "w");
     question8(input_file, output_file);
    printf("\n");


    //Display monthly average temperature from 1900-2015
    printquestion3(monthly_totals, monthly_counts);
    printf("\n");

    //Display hottest and coldest month recorded
    printquestion4(hottest_temp, hottest_month, hottest_year, coldest_temp, coldest_month, coldest_year);

    rewind(file);
    question11(file);

    rewind(file);
    question9(file);

    rewind(file);

  // writing file for question10
    FILE *in = fopen("question10.txt", "w");
    fprintf(in,"# Month AvgTemp Uncertainty\n");

    while (fgets(line, sizeof(line), file)) {
        question10(in,line, monthly_totals, monthly_counts, monthly_uncertainty);
    }

  // Calculate and print the average temperature and uncertainty for each month
    for (int i = 0; i < MAX_MONTHS; i++) {
      if (monthly_counts[i] > 0) {
          double avg_temperature = monthly_totals[i] / monthly_counts[i];
          double avg_uncertainty = monthly_uncertainty[i] / monthly_counts[i];
          fprintf(in, "%.2d %.2lf %.2lf\n", i+1, avg_temperature, avg_uncertainty);
      }
  }
    printf("\n");
    fclose(in);
    // Close file
    fclose(file);
    fclose(output_file);
    return 0;
}


