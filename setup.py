import os

years = [2025, 2026]
months = [
    "January", "February", "March", "April", "May", "June",
    "July", "August", "September", "October", "November", "December"
]

for year in years:
    for month in months:
        path = os.path.join(str(year), month)
        os.makedirs(path, exist_ok=True)
        # GitHub doesn't track empty folders, so add a .gitkeep
        gitkeep = os.path.join(path, ".gitkeep")
        with open(gitkeep, "w") as f:
            pass