<script lang="ts">
  export let url;
  export let path;
  export let value;
  export let title;

  let button;

  async function setBrightness() {
    let isOK = false;
    try {
      button.classList.add("gray-bg");
      let response = await fetch(`${url}/${path}?value=${value}`);
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
<button bind:this={button} on:click={setBrightness}>{title}</button>
