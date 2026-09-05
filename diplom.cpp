import random
import statistics
from pathlib import Path
import pandas as pd
import matplotlib.pyplot as plt
  
# Параметры модели
ADV_INTERVAL_S = 0.100
ADV_DELAY_MAX_S = 0.010
PACKET_DURATION_US = 376
BUSY_TIME_US = 1428
REPEAT_DISCOVERY_DELAY_S = 1.0
OBSERVATION_TIME_S = REPEAT_DISCOVERY_DELAY_S
TRIALS = 300
N_VALUES = [1, 5, 10, 20, 30, 40, 50, 75, 100, 125, 150, 175, 200, 250, 300]
CHANNEL_COUNTS = [1, 2, 3]
OUTPUT_DIR = Path("ble_model_output")
OUTPUT_DIR.mkdir(exist_ok=True)

# Вспомогательные функции
def channel_label(n_channels: int) -> str:
if n_channels == 1:
return "1 рекламный канал"
return f"{n_channels} рекламных канала"

# Генерация событий
def generate_events(
n_devices,
n_channels,
adv_interval_s,
adv_delay_max_s,
observation_time_s,
rng
):
events = []

for device_id in range(n_devices):
t = rng.random() * adv_interval_s

while t <= observation_time_s:
channel = rng.randrange(n_channels)

events.append((t, device_id, channel))

t += adv_interval_s + rng.random() * adv_delay_max_s

events.sort(key=lambda x: x[0])
return events

# Один прогон модели
def simulate_one_trial(
n_devices,
n_channels,
adv_interval_s=ADV_INTERVAL_S,
adv_delay_max_s=ADV_DELAY_MAX_S,
busy_time_us=BUSY_TIME_US,
observation_time_s=OBSERVATION_TIME_S,
seed=None
):
rng = random.Random(seed)
busy_time_s = busy_time_us * 1e-6

events = generate_events(
n_devices=n_devices,
n_channels=n_channels,
adv_interval_s=adv_interval_s,
adv_delay_max_s=adv_delay_max_s,
observation_time_s=observation_time_s,
rng=rng
)

discovered_time = [None] * n_devices
events_count = len(events)

for i, (t, device_id, channel) in enumerate(events):
if discovered_time[device_id] is not None and discovered_time[device_id]
<= t:

continue

collision = False

j = i - 1
while j >= 0 and (t - events[j][0]) < busy_time_s:
other_t, other_device, other_channel = events[j]
if other_device != device_id and other_channel == channel:

if discovered_time[other_device] is None or

discovered_time[other_device] > other_t:
collision = True
break

j -= 1

if not collision:
j = i + 1
while j < events_count and (events[j][0] - t) < busy_time_s:
other_t, other_device, other_channel = events[j]

if other_device != device_id and other_channel == channel:
if discovered_time[other_device] is None or

discovered_time[other_device] > other_t:
collision = True
break

j += 1
if not collision:
discovered_time[device_id] = t

successful_devices = sum(
1 for t in discovered_time
if t is not None and t <= observation_time_s
)

success_probability = successful_devices / n_devices
delay_with_timeout_s = [
t if t is not None else observation_time_s
for t in discovered_time
]
avg_delay_with_timeout_s = statistics.mean(delay_with_timeout_s)

return {
"success_probability": success_probability,
"avg_delay_with_timeout_ms": avg_delay_with_timeout_s * 1000,
"successful_devices": successful_devices,
"total_devices": n_devices
}

# Серия прогонов Монте-Карло
def run_model():
all_results = []
rng = random.Random(2026)

for n_channels in CHANNEL_COUNTS:
for n_devices in N_VALUES:
trial_results = []

for _ in range(TRIALS):
result = simulate_one_trial(
n_devices=n_devices,
n_channels=n_channels,
seed=rng.randrange(10**9)
)
trial_results.append(result)

row = {
"devices": n_devices,
"advertising_channels": n_channels,
"success_probability": statistics.mean([
r["success_probability"] for r in trial_results
]),
"avg_delay_with_timeout_ms": statistics.mean([
r["avg_delay_with_timeout_ms"] for r in trial_results
]),
"avg_successful_devices": statistics.mean([
r["successful_devices"] for r in trial_results
])
}

all_results.append(row)

print(
f"Каналов: {n_channels}, устройств: {n_devices}, "
f"Pусп = {row['success_probability']:.3f}, "
f"средняя задержка = {row['avg_delay_with_timeout_ms']:.1f} мс"
)

return pd.DataFrame(all_results)

# Построение графиков

def plot_delay_with_timeout(results):
plt.figure(figsize=(10, 5.5))

for n_channels in CHANNEL_COUNTS:
data = results[results["advertising_channels"] == n_channels]
plt.plot(
data["devices"],
data["avg_delay_with_timeout_ms"],
marker="o",
label=channel_label(n_channels)
)

plt.xlabel("Количество периферийных устройств, N")
plt.ylabel("Средняя задержка первичного доступа с учетом тайм-аута, мс")
plt.title("Зависимость средней задержки первичного доступа BLE от числа
устройств")
plt.ylim(0, OBSERVATION_TIME_S * 1000 * 1.05)
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig(OUTPUT_DIR / "ble_delay_with_timeout_vs_devices.png", dpi=300)
plt.show()

def plot_success_probability(results):
"""Строит график вероятности успешного обнаружения."""
plt.figure(figsize=(10, 5.5))

for n_channels in CHANNEL_COUNTS:
data = results[results["advertising_channels"] == n_channels]
plt.plot(
data["devices"],
data["success_probability"] * 100,
marker="o",
label=channel_label(n_channels)
)

plt.xlabel("Количество периферийных устройств, N")
plt.ylabel("Вероятность успешного обнаружения, %")
plt.title("Зависимость вероятности успешного обнаружения BLE-устройств от
числа устройств")
plt.ylim(0, 105)
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig(OUTPUT_DIR / "ble_success_probability_vs_devices.png", dpi=300)
plt.show()

# Основная функция
def main():
results = run_model()

results["success_probability_percent"] = results["success_probability"] *
100

csv_path = OUTPUT_DIR / "ble_model_results.csv"
results.to_csv(csv_path, index=False, encoding="utf-8-sig")

print("\nИтоговая таблица результатов:")
print(results)
print(f"\nРезультаты сохранены в папку: {OUTPUT_DIR.resolve()}")
plot_delay_with_timeout(results)
plot_success_probability(results)

if __name__ == "__main__":
main()
