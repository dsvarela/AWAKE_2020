"""Use Matpltlib to graph variables imported with Pickle."""
import numpy as np
import matplotlib.pyplot as plt
import pickle


with open("millis.txt", "rb") as fp:
    millis = pickle.load(fp)


with open("count.txt", "rb") as fp:
    count = pickle.load(fp)


with open("mult.txt", "rb") as fp:
    mult = pickle.load(fp)


class Cursor:
    """Add Cursor."""

    def __init__(self, ax):
        self.ax = ax
        self.lx = ax.axhline(color='k')  # the horiz line
        self.ly = ax.axvline(color='k')  # the vert line

        # text location in axes coords
        self.txt = ax.text(0.7, 0.9, '', transform=ax.transAxes)

    def mouse_move(self, event):
        """Update Crosshairs."""
        if not event.inaxes:
            return

        x, y = event.xdata, event.ydata
        # update the line positions
        self.lx.set_ydata(y)
        self.ly.set_xdata(x)

        self.txt.set_text('x=%1.2f, y=%1.2f' % (x, y))
        self.ax.figure.canvas.draw()


class SnaptoCursor:
    """
    Like Cursor but the crosshair snaps to the nearest x, y point.

    For simplicity, this assumes that *x* is sorted.
    """

    def __init__(self, ax, x, y):
        self.ax = ax
        self.lx = ax.axhline(color='k')  # the horiz line
        self.ly = ax.axvline(color='k')  # the vert line
        self.x = x
        self.y = y
        # text location in axes coords
        self.txt = ax.text(0.7, 0.9, '', transform=ax.transAxes)

    def mouse_move(self, event):
        """Update Crosshairs."""
        if not event.inaxes:
            return

        x, y = event.xdata, event.ydata
        indx = min(np.searchsorted(self.x, x), len(self.x) - 1)
        x = self.x[indx]
        y = self.y[indx]
        # update the line positions
        self.lx.set_ydata(y)
        self.ly.set_xdata(x)

        self.txt.set_text('x=%1.2f, y=%1.2f' % (x, y))
        print('x=%1.2f, y=%1.2f' % (x, y))
        self.ax.figure.canvas.draw()


"""
fig, ax = plt.subplots()
ax.plot(millis, mult)
cursor = Cursor(ax)
fig.canvas.mpl_connect('motion_notify_event', cursor.mouse_move)
"""

fig, ax = plt.subplots()
ax.plot(millis, mult)
ax.set_xlim([100, 20000])
ax.set_ylim([125, 40000])
# snap_cursor = SnaptoCursor(ax, millis, mult)
# fig.canvas.mpl_connect('motion_notify_event', snap_cursor.mouse_move)

plt.show()
