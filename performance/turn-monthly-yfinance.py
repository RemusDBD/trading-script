# Author : RemusDBD
# Update : 2025/01/05
# Change the line 60-63 user input.
import yfinance as yf
from datetime import datetime

# Function to parse vertical input for tickers
def parse_tickers(input_str):
    return [line.strip() for line in input_str.splitlines() if line.strip()]

# Function to calculate monthly performance
def get_specific_month_performance(tickers, year, month):
    performance = {}
    current_date = datetime.now()

    # Check if the input date is in the future
    if year > current_date.year or (year == current_date.year and month > current_date.month):
        print("Error: The specified month and year are in the future. Please select a valid past date.")
        return performance

    for ticker in tickers:
        try:
            # Fetch data for the past two years
            data = yf.download(ticker, period="2y", interval="1d", progress=False)
            if data.empty:
                continue

            # Add year-month column
            data['YearMonth'] = data.index.to_period('M')

            # Define target and previous months
            target_month = f"{year}-{month:02d}"
            prev_month = f"{year}-{month - 1:02d}" if month > 1 else f"{year - 1}-12"

            # Get closing prices for the target and previous months
            target_data = data[data['YearMonth'] == target_month]
            prev_data = data[data['YearMonth'] == prev_month]

            if target_data.empty or prev_data.empty:
                continue

            # Use the last available close in the month for calculation
            target_close = float(target_data['Close'].iloc[-1])
            prev_close = float(prev_data['Close'].iloc[-1])

            # Calculate monthly change
            monthly_change = ((target_close - prev_close) / prev_close) * 100
            performance[ticker] = round(monthly_change, 2)

        except Exception as e:
            print(f"Error processing {ticker}: {e}")
            continue

    return performance

# Example usage
if __name__ == "__main__":
    # User Input below
    user_input = """
    AAPL
    TSLA
    NVDA
    AVGO
    """
    tickers = parse_tickers(user_input)

    # User-specified month and year
    year = int(input("Enter the year (e.g. : 2024): "))
    month = int(input("Enter the month (e.g. : 1-12): "))

    # Get performance for the specific month
    monthly_performance = get_specific_month_performance(tickers, year, month)

    # Print results
    print(monthly_performance)

    # Print summary
    input_count = len(tickers)
    output_count = len(monthly_performance)
    print(f"\nSummary: {input_count} tickers were input, {output_count} results were output.")

    # Check for missing tickers
    missing_tickers = set(tickers) - set(monthly_performance.keys())
    if missing_tickers:
        print(f"Missing tickers (data unavailable or error): {', '.join(missing_tickers)}")

