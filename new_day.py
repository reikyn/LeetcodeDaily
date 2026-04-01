import os, sys
from datetime import date

def create_daily(problem_number, title_slug):
    today = date.today()
    year = str(today.year)
    month = today.strftime("%B")  # e.g., "April"
    folder_name = f"{int(problem_number):04d}-{title_slug}"
    path = os.path.join(year, month, folder_name)
    os.makedirs(path, exist_ok=True)

    for filename in ["solution.py", "solution.cpp"]:
        filepath = os.path.join(path, filename)
        if not os.path.exists(filepath):
            with open(filepath, "w") as f:
                pass  # empty file, you fill it in
    
    print(f"Created: {path}")

# Usage: python new_day.py 3342 find-minimum-time-to-reach-last-room-i
if __name__ == "__main__":
    create_daily(sys.argv[1], sys.argv[2])