# Author : RemusDBD
# Update : 2024/12/21
# Change the line 5 user input.
# Input the stock data
stocks = {'AAPL': 50.65, 'TSLA': 1609.16, 'NVDA': 23.98, 'AVGO': 150.0}

# Sort the stocks: positive percentages descending and negative percentages ascending
sorted_stocks = sorted(stocks.items(), key=lambda x: (x[1], x[0]), reverse=True)

# Format the sorted stocks into a string for output
output = ""
for stock_name, percentage in sorted_stocks:
    output += f"{stock_name} {percentage:.2f}% | "

# Count the number of input and output tickers
input_count = len(stocks)
output_count = len(sorted_stocks)

# Prepare final output
output = output.strip(' | ')
final_output = f"Input Tickers: {input_count}, Output Tickers: {output_count}\n{output}"

# Print the final output
print(final_output)
