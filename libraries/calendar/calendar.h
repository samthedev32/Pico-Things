#pragma once

char *__calendar_months[] = {
    "january", "february", "march",     "april",   "may",      "june",
    "july",    "august",   "september", "october", "november", "december",
};

char *__calendar_weekdays[] = {
    "monday", "tuesday",  "wednesday", "thursday",
    "friday", "saturday", "sunday",
};

typedef struct date {
  int year, month, day;
  int hour, minute, second, ms;
} date;

int calendar_get_days_of_month(date *d) {
  if (d->month == 02) {
    if (d->year % 4 == 0) {
      // leap year / szökőév
      return 29;
    }
    return 28;
  }
  if (d->month <= 7) {
    return 30 + (d->month % 2);
  } else {
    return 31 - (d->month % 2);
  }
}

void calendar_add_date(date *date, int y, int m, int d) {
  for (int i = 0; i < d; i++) {
    if (date->day == calendar_get_days_of_month(date)) {
      date->day = 1;
      m++;
    } else {
      date->day++;
    }
  }

  for (int i = 0; i < m; i++) {
    if (date->month == 12) {
      date->month = 1;
      y++;
    } else {
      date->month++;
    }
  }

  date->year += y;
}

void calendar_add_time(date *d, int h, int m, int s) {
  for (int i = 0; i < s; i++) {
    d->second++;

    if (d->second >= 60) {
      d->second -= 60;
      m++;
    }
  }

  for (int i = 0; i < m; i++) {
    d->minute++;

    if (d->minute >= 60) {
      d->minute -= 60;
      h++;
    }
  }

  for (int i = 0; i < h; i++) {
    d->hour++;

    if (d->hour >= 24) {
      d->hour -= 24;
      calendar_add_date(d, 0, 0, 1);
    }
  }
}

int calendar_is_leap_year(date *d) { return d->year % 4; }

char *calendar_get_month(date *d) { return __calendar_months[d->month - 1]; }

char *calendar_get_day(date *d) {
  if (d->year >= 2001) {
    int dayCount = 0;

    date d2;
    d2.year = 2001;
    d2.month = 01;
    d2.day = 01;

    while (d2.year != d->year || d2.month != d->month || d2.day != d->day) {
      dayCount++;
      calendar_add_date(&d2, 0, 0, 1);
    }

    return __calendar_weekdays[(dayCount) % 7];
  } else if (d->year < 2001) {
    int dayCount = 0;

    date d2;
    d2.year = d->year;
    d2.month = d->month;
    d2.day = d->day;

    while (d2.year != 2001 || d2.month != 01 || d2.day != 01) {
      dayCount++;
      calendar_add_date(&d2, 0, 0, 1);
    }

    return __calendar_weekdays[7 - ((dayCount) % 7)];
  }
  return "";
}