<script lang="ts">
  export let url;
  let maxBrightness = 100;
  let selectedBrightness = 10;
  let button;

  async function setBrightness() {
    let isOK = false;
    try {
      button.classList.add("gray-bg");
      let response = await fetch(`${url}/brightness?value=${selectedBrightness}`);
      isOK = response.ok;
    } catch (error) {
      isOK = false;
    }
    if (isOK) {
      button.classList.add("green-bg");
      setTimeout(() => {
        button.classList.remove("green-bg");
        button.classList.remove("gray-bg");
      }, 500);
    } else {
      button.classList.add("red-bg");
      setTimeout(() => {
        button.classList.remove("red-bg");
        button.classList.remove("gray-bg");
      }, 500);
    }
  }
</script>

Max Brightness: <input
  type="number"
  min="0"
  max="255"
  bind:value={maxBrightness}
/>
<div class="slidecontainer">
  <input
    type="range"
    min="1"
    max={maxBrightness}
    bind:value={selectedBrightness}
  /> {selectedBrightness}
</div>
<button bind:this={button} on:click={setBrightness}>Set Brightness</button>
<style>
</style>
