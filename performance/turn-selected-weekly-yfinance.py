# Author : RemusDBD
# Update : 2025/01/11
# Change the line 43-68 user input.
import yfinance as yf
import pandas as pd

# Function to parse vertical input for tickers
def parse_tickers(input_str):
    # Split the input string by newlines and remove empty lines or extra spaces
    tickers = [line.strip() for line in input_str.splitlines() if line.strip()]
    return tickers

# Function to calculate weekly performance
def get_weekly_performance(tickers, target_friday):
    results = {}
    missing_tickers = []
    target_date = pd.to_datetime(target_friday)
    start_date = target_date - pd.Timedelta(days=7)
    end_date = target_date + pd.Timedelta(days=1)

    for ticker in tickers:
        try:
            # Fetch historical data for the ticker
            data = yf.download(ticker, start=start_date.strftime('%Y-%m-%d'), end=end_date.strftime('%Y-%m-%d'), progress=False)
            data.index = pd.to_datetime(data.index)

            # Locate prices for the prior Friday and target Friday
            prior_friday_close = float(data.loc[start_date.strftime('%Y-%m-%d'), "Close"].iloc[0])  # Legacy method
            target_friday_close = float(data.loc[target_friday, "Close"].iloc[0])  # Legacy method

            # Calculate percentage change
            performance = ((target_friday_close - prior_friday_close) / prior_friday_close) * 100
            results[ticker] = round(performance, 2)
        except Exception as e:
            missing_tickers.append(ticker)

    return results, missing_tickers

# Main script
if __name__ == "__main__":
    try:
        # User input. Change the below
        target_friday = "2025-01-03"  # Specify the Friday/last trading date of the week (YYYY-MM-DD)
        user_input = """
AAPL
TSLA
NVDA
AVGO
        """

        # Parse tickers
        tickers = parse_tickers(user_input)

        # Get weekly performance
        weekly_performance, missing_tickers = get_weekly_performance(tickers, target_friday)

        # Print results
        print("\nWeekly Performance:")
        print(weekly_performance)

        # Print summary
        input_count = len(tickers)
        output_count = len(weekly_performance)
        print(f"\nSummary: {input_count} tickers were input, {output_count} results were output.")
        
        # Check for missing tickers
        if missing_tickers:
            print(f"Missing tickers (data unavailable or error): {', '.join(missing_tickers)}")

    except Exception as e:
        print(f"An error occurred: {e}")
