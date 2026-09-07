import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from matplotlib.patches import FancyArrow, Rectangle
import matplotlib.lines as mlines

fig, ax = plt.subplots(figsize=(16, 15))

actors = [
    ("Customer", 0),
    ("CinemaMenu", 1),
    ("BookingService", 2),
    ("Show", 3),
    ("ShowSeat", 4),
    ("PriceCalculator", 5),
    ("Booking", 6),
    ("UpiPayment", 7),
    ("TicketPrinter", 8),
]
n = len(actors)
xs = {name: i * 2.2 for name, i in actors}
top = 34
bottom = -3

# Draw lifeline headers and lines
for name, i in actors:
    x = xs[name]
    ax.add_patch(Rectangle((x - 0.9, top), 1.8, 1.0, facecolor="#2c3e50", edgecolor="black", zorder=3))
    ax.text(x, top + 0.5, name, ha="center", va="center", color="white", fontsize=10, fontweight="bold", zorder=4)
    ax.plot([x, x], [top, bottom], color="gray", linestyle="dashed", linewidth=1, zorder=1)

# helper for activation bars
def activation(name, y1, y2, width=0.18):
    x = xs[name]
    ax.add_patch(Rectangle((x - width, y2), width * 2, y1 - y2, facecolor="#dfe6ee", edgecolor="black", zorder=2))

def msg(src, dst, y, text, dashed=False, create=False, note=None):
    x1, x2 = xs[src], xs[dst]
    color = "black"
    style = "dashed" if dashed else "solid"
    ax.annotate("", xy=(x2, y), xytext=(x1, y),
                arrowprops=dict(arrowstyle="-|>" if not dashed else "-|>",
                                 linestyle=style, color=color, lw=1.4,
                                 shrinkA=2, shrinkB=2), zorder=5)
    midx = (x1 + x2) / 2
    label = text if not create else text + "  «create»"
    ax.text(midx, y + 0.28, label, ha="center", va="bottom", fontsize=8.3, zorder=6)

# Activation bars (approx spans)
activation("CinemaMenu", 32.5, 2.9)
activation("BookingService", 31.3, 13.6)
activation("Show", 30.0, 28.6)
activation("ShowSeat", 28.8, 25.0)
activation("PriceCalculator", 24.2, 22.6)
activation("Booking", 22.0, 20.6)
activation("Booking", 9.4, 8.0)
activation("UpiPayment", 13.5, 10.3)
activation("TicketPrinter", 6.5, 4.9)

y = 33
msg("Customer", "CinemaMenu", y, "choose show, seat, pay by UPI"); y -= 1.5
msg("CinemaMenu", "BookingService", y, "bookSeats(show, customer, seatNumbers)"); y -= 1.6
msg("BookingService", "Show", y, "getShowSeats()"); y -= 1.4
msg("Show", "BookingService", y, "showSeats list", dashed=True); y -= 1.6
msg("BookingService", "ShowSeat", y, "isAvailable()"); y -= 1.3
msg("ShowSeat", "BookingService", y, "true", dashed=True); y -= 1.5
msg("BookingService", "ShowSeat", y, "book()"); y -= 1.3
msg("ShowSeat", "BookingService", y, "status = BOOKED", dashed=True); y -= 1.6
msg("BookingService", "PriceCalculator", y, "calculateTotal(bookedSeats)"); y -= 1.4
msg("PriceCalculator", "BookingService", y, "totalAmount", dashed=True); y -= 1.6
msg("BookingService", "Booking", y, "new Booking(show, customer, seats, amt)", create=True); y -= 1.4
msg("Booking", "BookingService", y, "booking (PENDING)", dashed=True); y -= 1.6
msg("BookingService", "CinemaMenu", y, "booking (PENDING)", dashed=True); y -= 1.8

msg("CinemaMenu", "UpiPayment", y, "new UpiPayment(upiId)", create=True); y -= 1.6
msg("CinemaMenu", "BookingService", y, "makePayment(booking, payment)"); y -= 1.5
msg("BookingService", "UpiPayment", y, "pay(totalAmount)"); y -= 1.4
msg("UpiPayment", "BookingService", y, "true", dashed=True); y -= 1.6
msg("BookingService", "Booking", y, "confirm()"); y -= 1.3
msg("Booking", "BookingService", y, "status = CONFIRMED", dashed=True); y -= 1.6
msg("BookingService", "TicketPrinter", y, "printTicket(booking)"); y -= 1.4
msg("TicketPrinter", "BookingService", y, "ticket printed", dashed=True); y -= 1.6
msg("BookingService", "CinemaMenu", y, "booking confirmed", dashed=True); y -= 1.5
msg("CinemaMenu", "Customer", y, "display ticket"); y -= 1

ax.set_xlim(-1.5, xs["TicketPrinter"] + 1.5)
ax.set_ylim(bottom - 1, top + 1.5)
ax.axis("off")
ax.set_title("Sequence Diagram: Customer books 1 seat and pays by UPI", fontsize=13, fontweight="bold", pad=10)
plt.tight_layout()
plt.savefig("/home/claude/assignment/diagrams/sequence_diagram.png", dpi=150, facecolor="white")
print("done")
