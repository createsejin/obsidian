`<user>\.glzr\zebar\starter\with-glazewm.html`을 열어서 
```css
      const providers = zebar.createProviderGroup({
        network: { type: 'network' },
        glazewm: { type: 'glazewm' },
        cpu: { type: 'cpu' },
        date: { type: 'date', formatting: 'yyyy-MM-dd HH:mm' },
        battery: { type: 'battery' },
        memory: { type: 'memory' },
        weather: { type: 'weather' },
      });
```
이 부분을 찾는다. 여기에서 `date:` 부분의 `formatting:` 부분을 수정해주면 된다.