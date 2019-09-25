# Exemplo 4.3 - Calculando o Dia do Ano

% Purpose:
%   This program calculates the day of year corresponding
%   to a specific date. It ilustrates the use switch and
%   for constructs.
%
% Define variables:
%   day 
%   month
%   year
%   day_of_year

disp('This program calculates the day of year given');
disp('the current date.');
disp('');

% Get the data
disp('Complete with the current date:');

day = input('day (1-31): ');
month = input('month (1-12): ');
year = input('year (yyyy): ');

% Check for leap year, and add extra day if necessary
if mod(year, 400) == 0
  leap_day = 1;             % Years divisible by 400 are leap years
elseif mod(year, 100) == 0
  leap_day = 0;             % Other centuries are not leap years

elseif mod(year, 4) == 1
  leap_day = 1;             % Otherwise every 4th year is a leap year
else
  leap_day = 0;             % Other years are not leap years
end

% Calculate the day of year by adding current day to the 
% days in previous months.
day_of_year = day;
for ii = 1 : month-1
  % Add days in months from January to last month
  switch(ii)
  case { 1, 3, 5, 7, 8, 10, 12 }, % months with 31 days
    day_of_year = day_of_year + 31;
  case { 4, 6, 9, 11 },  % months with 30 days
    day_of_year = day_of_year + 30;
  case 2,  % february
    day_of_year = day_of_year + 28 + leap_day;
  end

end

% Tell user
fprintf('The date %2d/%2d/%4d is a day year %d.\n', ...
day, month, year, day_of_year);
