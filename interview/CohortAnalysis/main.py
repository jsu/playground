#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import pandas as pd

if __name__ == "__main__":
    customer_df = pd.read_csv("customers.csv")
    print(customer_df.head())
    sorted_df = customer_df.sort_values("created")
    print(sorted_df.head(n=3))
    print(customer_df.iloc[:,1].min())

    order_df = pd.read_csv("orders.csv")
    print(order_df.head())
    print(order_df.iloc[[:,1], df.columns.get_loc("created"))
