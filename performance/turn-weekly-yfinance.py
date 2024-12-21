# Author : RemusDBD
# Update : 2024/12/21
# Change the line 48-51 user input.
import yfinance as yf

# Function to parse vertical input for tickers
def parse_tickers(input_str):
    # Split the input string by newlines and remove empty lines or extra spaces
    tickers = [line.strip() for line in input_str.splitlines() if line.strip()]
    return tickers

# Function to calculate weekly performance
def get_weekly_performance(tickers):
    performance = {}

    for ticker in tickers:
        try:
            # Fetch one month's data (to ensure we capture at least two Fridays)
            data = yf.download(ticker, period="1mo", interval="1d", progress=False)
            
            if data.empty:
                continue
            
            # Add a 'Day' column to identify Fridays
            data['Day'] = data.index.day_name()
            fridays = data[data['Day'] == 'Friday']
            
            # Ensure at least two Fridays exist in the data
            if len(fridays) < 2:
                continue
            
            # Get the last two Fridays
            last_week_close = float(fridays.iloc[-2]['Close'])  # Previous Friday close
            current_week_close = float(fridays.iloc[-1]['Close'])  # Latest Friday close
            
            # Calculate percentage change
            weekly_change = ((current_week_close - last_week_close) / last_week_close) * 100
            performance[ticker] = round(weekly_change, 2)
        except Exception:
            continue

    return performance

# Example usage
if __name__ == "__main__":
    # Example user input in vertical format
    user_input = """ 
    AAPL
    TSLA
    NVDA
    AVGO
    """
    
    # Parse the user input
    tickers = parse_tickers(user_input)
    
    # Get weekly performance
    weekly_performance = get_weekly_performance(tickers)
    
    # Print results
    print()
    print(weekly_performance)
    
    # Print summary
    input_count = len(tickers)
    output_count = len(weekly_performance)
    print(f"\nSummary: {input_count} tickers were input, {output_count} results were output.")
    
    # Check for missing tickers
    missing_tickers = set(tickers) - set(weekly_performance.keys())
    if missing_tickers:
        print(f"Missing tickers (data unavailable or error): {', '.join(missing_tickers)}")

