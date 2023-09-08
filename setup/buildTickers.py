import pandas as pd

# Scrape the table from Wikipedia
url = "https://en.wikipedia.org/wiki/List_of_S%26P_500_companies"
table = pd.read_html(url)[0]  # The first table on the page contains the tickers

# Save the 'Symbol' column to a CSV file
table["Symbol"].to_csv("tickers.csv", index=False)