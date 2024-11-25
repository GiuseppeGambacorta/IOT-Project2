import customtkinter as ctk
import matplotlib.pyplot as plt


def create_real_time_plots():
        fig, (ax1, ax2) = plt.subplots(figsize=(12, 6), ncols=2)
        ax1.set_title("Temperature")
        ax1.set_xlabel("Time")
        ax1.set_ylabel("Value")

        ax2.set_title("Temperature")
        ax2.set_xlabel("Time")
        ax2.set_ylabel("Value")

        return fig, (ax1, ax2)