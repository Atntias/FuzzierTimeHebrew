#include "num2words.h"
#include "string.h"

static const char* const ONES[] = {
  "          xpt ",
  "          sjt ",
  "         oh,a ",
  "         auka ",
  "         gcrt ",
  "          anj ",
  "           aa ",
  "          gca ",
  "        vbuna ",
  "           ga, "
};

static const char* const TEENS[] ={
  "",
  "   vrag sjt ",
  "     vrag oh,a ",
  "     vrag auka ",
  "     vrag gcrt ",
  "      vrag anj ",
  "       vrag aa ",
  "      vrag gca ",
  "    vrag vbuna ",
  "      vrag ga, "
};

static const char* const TENS[] = {
  "",
  "          rag ",
  "       ohragu ",
  "       ohauka ",
  "       ohgcrt ",
  "       ohahnj ",
  "        ohaha ",
  "       ohgcha ",
  "       ohbuna ",
  "        ohga, "
};


static const char* STR_NOON     = "ohhrvm";
static const char* STR_MIDNIGHT = ",umj";
static const char* STR_QUARTER  = "          gcru ";
static const char* STR_AQUARTER = "          gcru ";
static const char* STR_TO       = "k";
static const char* STR_PAST     = "hrjt";
static const char* STR_HALF     = "            hmju ";
static const char* STR_AFTER    = "hrjt";
static const char* STR_ALMOST   = "          ygnf ";
static const char* STR_LITTLE   = ",me";
static const char* STR_ALITTLE  = "          ,meu ";
static const char* STR_ABOUT    = "          lrgc ";
static const char* STR_AROUND   = "        ,uchcx ";
static const char* STR_TWENTY   = "ohragu";

static size_t append_number(char* words, int num) {
  int tens_val = num / 10 % 10;
  int ones_val = num % 10;

  size_t len = 0;

  if (tens_val > 0) {
    if (tens_val == 1 && num != 10) {
      strcat(words, TEENS[ones_val]);
      return strlen(TEENS[ones_val]);
    }
    strcat(words, TENS[tens_val]);
    len += strlen(TENS[tens_val]);
    if (ones_val > 0) {
      strcat(words, " ");
      len += 1;
    }
  }

  if (ones_val > 0 || num == 0) {
    strcat(words, ONES[ones_val]);
    len += strlen(ONES[ones_val]);
  }
  return len;
}

static size_t append_string(char* buffer, const size_t length, const char* str) {
  strncat(buffer, str, length);

  size_t written = strlen(str);
  return (length > written) ? written : length;
}

void fuzzy_time_to_words(int hours, int minutes, char* words, size_t length) {
  int fuzzy_hours = hours;
  int fuzzy_minutes = minutes;

  size_t remaining = length;
  memset(words, 0, length);
	
    if (fuzzy_minutes < 4) {
 	  remaining -= append_string(words, remaining, STR_AROUND);
	 if (fuzzy_hours == 0) {remaining -= append_string(words, remaining, STR_MIDNIGHT);} else if (fuzzy_hours == 12) {remaining -= append_string(words, remaining, STR_NOON);} else {remaining -= append_number(words, fuzzy_hours % 12);}      
	} else if (fuzzy_minutes > 56 && fuzzy_minutes <= 59) {
	  remaining -= append_string(words, remaining, STR_AROUND); 
	  fuzzy_hours = (fuzzy_hours + 1) % 24; //add and hour
	  if (fuzzy_hours == 0) {remaining -= append_string(words, remaining, STR_MIDNIGHT);} else if (fuzzy_hours == 12) {remaining -= append_string(words, remaining, STR_NOON);} else {remaining -= append_number(words, fuzzy_hours % 12);}	  
	} else if (fuzzy_minutes > 3 && fuzzy_minutes < 13) { 
	  if (fuzzy_hours == 0) {remaining -= append_string(words, remaining, STR_MIDNIGHT);} else if (fuzzy_hours == 12) {remaining -= append_string(words, remaining, STR_NOON);} else {remaining -= append_number(words, fuzzy_hours % 12);}
	  remaining -= append_string(words, remaining, STR_ALITTLE);
	} else if (fuzzy_minutes > 12 && fuzzy_minutes < 19) {//19
	  remaining -= append_string(words, remaining, STR_AROUND);
      if (fuzzy_hours == 0) {remaining -= append_string(words, remaining, STR_MIDNIGHT);} else if (fuzzy_hours == 12) {remaining -= append_string(words, remaining, STR_NOON);} else {remaining -= append_number(words, fuzzy_hours % 12);}      
	  remaining -= append_string(words, remaining, STR_QUARTER);
	} else if (fuzzy_minutes > 18 && fuzzy_minutes < 24) {
	  remaining -= append_string(words, remaining, STR_ABOUT);
      if (fuzzy_hours == 0) {remaining -= append_string(words, remaining, STR_MIDNIGHT);} else if (fuzzy_hours == 12) {remaining -= append_string(words, remaining, STR_NOON);} else {remaining -= append_number(words, fuzzy_hours % 12);}         
	  remaining -= append_string(words, remaining, STR_TWENTY);
	} else if (fuzzy_minutes > 23 && fuzzy_minutes < 28) {
	  remaining -= append_string(words, remaining, STR_ALMOST);
      if (fuzzy_hours == 0) {remaining -= append_string(words, remaining, STR_MIDNIGHT);} else if (fuzzy_hours == 12) {remaining -= append_string(words, remaining, STR_NOON);} else {remaining -= append_number(words, fuzzy_hours % 12);}              		
	  remaining -= append_string(words, remaining, STR_HALF);
	} else if (fuzzy_minutes > 27 && fuzzy_minutes < 34) {
	  remaining -= append_string(words, remaining, STR_ABOUT);  
	  if (fuzzy_hours == 0) {remaining -= append_string(words, remaining, STR_MIDNIGHT);} else if (fuzzy_hours == 12) {remaining -= append_string(words, remaining, STR_NOON);} else {remaining -= append_number(words, fuzzy_hours % 12);}      	    		
	  remaining -= append_string(words, remaining, STR_HALF);
	} else if (fuzzy_minutes > 33 && fuzzy_minutes < 39) {
	  remaining -= append_string(words, remaining, STR_LITTLE);
	  remaining -= append_string(words, remaining, STR_AFTER);
	  if (fuzzy_hours == 0) {remaining -= append_string(words, remaining, STR_MIDNIGHT);} else if (fuzzy_hours == 12) {remaining -= append_string(words, remaining, STR_NOON);} else {remaining -= append_number(words, fuzzy_hours % 12);}	
	  remaining -= append_string(words, remaining, STR_HALF);	
	} else if (fuzzy_minutes > 38 && fuzzy_minutes < 43) {
	  remaining -= append_string(words, remaining, STR_ALMOST);    
      remaining -= append_string(words, remaining, STR_QUARTER);
      remaining -= append_string(words, remaining, STR_TO);
	  fuzzy_hours = (fuzzy_hours + 1) % 24;
	  if (fuzzy_hours == 0) {remaining -= append_string(words, remaining, STR_MIDNIGHT);} else if (fuzzy_hours == 12) {remaining -= append_string(words, remaining, STR_NOON);} else {remaining -= append_number(words, fuzzy_hours % 12);}      	    		
	} else if (fuzzy_minutes > 42 && fuzzy_minutes < 50) {
	  remaining -= append_string(words, remaining, STR_AROUND);
	  remaining -= append_string(words, remaining, STR_QUARTER);
	  remaining -= append_string(words, remaining, STR_TO);
      fuzzy_hours = (fuzzy_hours + 1) % 24;
	  if (fuzzy_hours == 0) {remaining -= append_string(words, remaining, STR_MIDNIGHT);} else if (fuzzy_hours == 12) {remaining -= append_string(words, remaining, STR_NOON);} else {remaining -= append_number(words, fuzzy_hours % 12);}			
	} else if (fuzzy_minutes > 49 && fuzzy_minutes < 57) { 
	  remaining -= append_string(words, remaining, STR_ALMOST); 
	  fuzzy_hours = (fuzzy_hours + 1) % 24;	  
      if (fuzzy_hours == 0) {remaining -= append_string(words, remaining, STR_MIDNIGHT);} else if (fuzzy_hours == 12) {remaining -= append_string(words, remaining, STR_NOON);} else {remaining -= append_number(words, fuzzy_hours % 12);}		    
    }
}
